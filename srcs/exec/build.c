/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 17:39:48 by abutet            #+#    #+#             */
/*   Updated: 2024/11/20 10:01:26 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_build(t_Minishell *mini, int i)
{
	if (!(mini->commande[i].cmd) && !(mini->commande[i].cmd[0]))
		return (0);
	if (!ft_strncmp("exit", mini->commande[i].cmd[0], 5))
		return (1);
	if (!ft_strncmp("echo", mini->commande[i].cmd[0], 5))
		return (1);
	if (!ft_strncmp("env", mini->commande[i].cmd[0], 4))
		return (1);
	if (!ft_strncmp("pwd", mini->commande[i].cmd[0], 4))
		return (1);
	if (!ft_strncmp("export", mini->commande[i].cmd[0], 7))
		return (1);
	if (!ft_strncmp("unset", mini->commande[i].cmd[0], 6))
		return (1);
	if (!ft_strncmp("cd", mini->commande[i].cmd[0], 3))
		return (1);
	return (0);
}

size_t	ft_maplen(char **map)
{
	size_t	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	free_cmd(int nbcmd, t_temp *commande)
{
	int	i;

	i = 0;
	if (!commande)
		return ;
	while (i <= nbcmd)
	{
		free_map(commande[i].cmd);
		i++;
	}
	free(commande);
}

void	close_build(t_Minishell *mini, int i)
{
	if (mini->commande[i].in > 0)
		close(mini->commande[i].in);
	if (mini->commande[i].out > 1)
		close(mini->commande[i].out);
}

int	build(t_struct *stru, t_Minishell *mini, int i)
{
	if (mini->commande[i].out < 0 || mini->commande[i].in < 0)
		return (close_build(mini, i), mini->exit_code = 1);
	if (!strncmp("exit", mini->commande[i].cmd[0], 5))
			mini->exit_code = ft_exit(mini->commande, stru->pipe, i, mini);
	if (!strncmp("echo", mini->commande[i].cmd[0], 5))
		mini->exit_code = ft_echo(&(mini->commande[i]));
	if (!strncmp("pwd", mini->commande[i].cmd[0], 4))
		mini->exit_code = pwd(&(mini->commande[i]));
	if (!strncmp("env", mini->commande[i].cmd[0], 4))
		mini->exit_code = my_env(&(mini->commande[i]), *(mini->envp));
	if (!strncmp("export", mini->commande[i].cmd[0], 7))
		mini->exit_code = export(&(mini->commande[i]), mini);
	if (!strncmp("unset", mini->commande[i].cmd[0], 7))
		mini->exit_code = unset(mini->envp[0], mini->noenv,
				&(mini->commande[i]));
	if (!strncmp("cd", mini->commande[i].cmd[0], 3))
		mini->exit_code = my_cd(&(mini->commande[i]), mini);
	close_build(mini, i);
	return (0);
}
