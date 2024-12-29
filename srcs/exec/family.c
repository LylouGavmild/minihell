/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   family.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:07:23 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/28 12:58:16 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all(t_temp *commande, int nbcmd)
{
	int	i;

	i = 0;
	while (i < nbcmd)
	{
		if (commande[i].in > 0)
			close(commande[i].in);
		if (commande[i].out > 1)
			close(commande[i].out);
		i++;
	}
}

void	childminder(t_struct *stru, t_temp *commande, t_Minishell *mini, int i)
{
	command_check(stru, commande, mini, i);
	(signal(SIGINT, SIG_DFL), signal(SIGQUIT, SIG_DFL));
	execve(stru->joined, commande[i].cmd, *(mini->envp));
	exit_fork(stru, mini, NULL, 0);
}

void	child_helper(t_struct *stru, t_Minishell *mini, int i)
{
	re_set_signal_action();
	free_btree(mini->origine);
	if (mini->commande[i].out == -1 || mini->commande[i].out == -2)
	{
		close_all(mini->commande, stru->pipe + 1);
		exit_fork(stru, mini, "", 0);
	}
	if (mini->commande[i].out > 1)
		dup2(mini->commande[i].out, 1);
	if (mini->commande[i].in == -2)
	{
		close_all(mini->commande, stru->pipe + 1);
		exit_fork(stru, mini, "", 0);
	}
	if (mini->commande[i].in == -1)
	{
		close_all(mini->commande, stru->pipe + 1);
		exit_fork(stru, mini, "", 1);
	}
	if (mini->commande[i].in > 0)
		dup2(mini->commande[i].in, 0);
	close_all(mini->commande, stru->pipe + 1);
	childminder(stru, mini->commande, mini, i);
}

void	child_one(t_struct *stru, t_Minishell *mini, int i)
{
	stru->ch = (pid_t *)ft_realloc(stru->ch,
			sizeof(pid_t) * (stru->i - mini->nbbuiltins),
			sizeof(pid_t) * (stru->i - mini->nbbuiltins + 1));
	if (!stru->ch)
		exit_close(stru);
	stru->ch[stru->i - mini->nbbuiltins] = fork();
	if (stru->ch[stru->i - mini->nbbuiltins] == 0)
		child_helper(stru, mini, i);
	if (mini->commande[i].out > 1)
		close(mini->commande[i].out);
	if (mini->commande[i].in > 0)
		close(mini->commande[i].in);
}
