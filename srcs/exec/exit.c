/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:22:08 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:22:35 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exit_exit(int err, int i, t_temp *commande, t_Minishell *mini)
{
	if (!i)
	{
		clear_history();
		free_cmd(i, commande);
		if (mini->envp)
		{
			if (*(mini->envp))
				free_map(*(mini->envp));
			free(mini->envp);
		}
		if (mini->noenv)
			free_map(mini->noenv);
		exit(err);
	}
	return (err);
}

void	exit_help(t_temp *commande, int j, int pipe, t_Minishell *mini)
{
	write(2, "minishell: exit:", 16);
	write(2, commande[j].cmd[1], ft_strlen(commande[j].cmd[1]));
	write(2, ": numeric argument required\n", 28);
	exit_exit(2, pipe, commande, mini);
}

int	othercmd(t_Node *root, int r)
{
	if (!root)
		return (0);
	r += othercmd(root->left, r);
	if (root->token.type == 1)
		r++;
	r += othercmd(root->right, r);
	return (r);
}

int	true_exit(char **cmd)
{
	int	i;

	i = ft_maplen(cmd) - 1;
	if (i == 0)
		return (1);
	else
	{
		if (!ft_is_numeric(cmd[1]) || ft_atocoi(cmd[1]))
			return (1);
		if (i > 1)
			return (0);
	}
	return (1);
}

int	ft_exit(t_temp *commande, int pipe, int j, t_Minishell *mini)
{
	int	exit_code;
	int	i;

	i = ft_maplen(commande[j].cmd) - 1;
	if (!pipe)
	{
		write(1, "exit\n", 5);
		if (i <= 1 && (!(othercmd(mini->origine, 0) - 1)
				|| true_exit(commande[j].cmd)))
		{
			close_all(commande, pipe + 1);
			free_btree(mini->origine);
		}
	}
	if (!i)
		exit_code = 0;
	else
	{
		if (!ft_is_numeric(commande[j].cmd[1]) || ft_atocoi(commande[j].cmd[1]))
			exit_help(commande, j, pipe, mini);
		if (i > 1)
			return (write(2, "minishell: exit: too many arguments\n", 36), 1);
		exit_code = ft_atoi(commande[j].cmd[1]);
	}
	return (exit_exit((unsigned char)exit_code, pipe, commande, mini));
}
