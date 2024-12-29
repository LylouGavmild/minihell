/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-rese <ade-rese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:32:14 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/29 15:09:19 by ade-rese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	prexit(t_struct *stru, t_Minishell *mini, int l, int i)
{
	write(2, "minishell: ", 11);
	write(2, mini->commande[l].cmd[0], ft_strlen(mini->commande[l].cmd[0]));
	if (i == 0)
		exit_fork(stru, mini, ": command not found\n", 127);
	if (i == 1)
		exit_fork(stru, mini, ": Permission denied\n", 126);
	if (i == 2)
		exit_fork(stru, mini, ": no such file or directory\n", 127);
}

static int	command_check_helper(t_struct *stru,
		t_Minishell *mini, int *err, int l)
{
	char	*tmp;
	int		i;

	i = -1;
	while (stru->spl_path[++i])
	{
		tmp = ft_strjoin(stru->spl_path[i], "/");
		stru->joined = ft_strjoin(tmp, (*(mini->commande[l].cmd)));
		if (!stru->joined)
			exit_fork(stru, mini, "minishell: stru->joined allocation fail\n",
				1);
		free(tmp);
		if (access(stru->joined, F_OK) == 0)
		{
			if (access(stru->joined, X_OK) == 0)
				return (1);
			err[0] = 1;
		}
		free(stru->joined);
	}
	return (0);
}

char	*command_check(t_struct *stru
	, t_temp *commande, t_Minishell *mini, int l)
{
	int		err;
	char	*path;

	err = check_if_dir(stru, commande, mini, l);
	if (access(commande[l].cmd[0], F_OK) == 0)
		if (access(commande[l].cmd[0], X_OK) == 0 || err++)
			return (stru->joined = commande[l].cmd[0]);
	if (commande[l].cmd[0][0] == '.')
	{
		if (err)
			return (prexit(stru, mini, l, err), NULL);
		return (prexit(stru, mini, l, 2), NULL);
	}
	path = pathset(mini, stru, l, err);
	stru->spl_path = ft_split(path, ':');
	free(path);
	if (!stru->spl_path)
		exit_fork(stru, mini, "minishell: spl_path allocation fail\n", 1);
	if (command_check_helper(stru, mini, &err, l))
		return (NULL);
	return (stru->joined = NULL, prexit(stru, mini, l, err), NULL);
}

int	micro_cmd(t_Minishell *mini, t_struct *stru)
{
	int	err;

	stru->pipe = mini->nbcmd - 1;
	stru->i = -1;
	mini->nbbuiltins = 0;
	while (++stru->i < (mini->nbcmd))
	{
		if (is_build(mini, stru->i))
		{
			mini->nbbuiltins++;
			build(stru, mini, stru->i);
		}
		else
		{
			child_one(stru, mini, stru->i);
		}
	}
	if ((stru->i - mini->nbbuiltins) != 0)
		err = wpids(stru, mini->nbbuiltins, mini);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (is_build(mini, stru->i - 1))
		return (mini->exit_code);
	return (err);
}

int	cmd(t_Minishell *mini)
{
	t_struct	stru;
	int			err;

	stru.i = 0;
	init_struct(&stru);
	err = micro_cmd(mini, &stru);
	return (free_struct(&stru), err);
}
