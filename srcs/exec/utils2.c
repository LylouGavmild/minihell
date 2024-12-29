/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:30:10 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/29 14:17:00 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*pathset(t_Minishell *mini, t_struct *stru, int l, int err)
{
	char	*path;

	path = expand(*(mini->envp), mini->noenv, "PATH");
	if (!path)
	{
		if (err)
			return (prexit(stru, mini, l, err), NULL);
		return (prexit(stru, mini, l, 2), NULL);
	}
	return (path);
}

int	exit_fperror(t_struct *stru, t_temp *commande, t_Minishell *mini, int num)
{
	write(2, "minishell: ", 11);
	if (commande->cmd[0])
		write(2, commande->cmd[0], ft_strlen(commande->cmd[0]));
	if (num == 2)
	{
		write(2, ": filename argument required\n", 29);
		exit_fork(stru, mini, ".: usage: . filename [arguments]\n", 2);
	}
	if (num == 126)
		exit_fork(stru, mini, ": Is a directory\n", 126);
	if (num == 127)
		exit_fork(stru, mini, ": command not found\n", 127);
	return (0);
}

char	*ft_strdup(char *s1)
{
	char	*r;
	size_t	len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	r = malloc(sizeof(char) * len);
	if (!r)
		return (NULL);
	r = ft_memcpy(r, s1, len);
	return (r);
}

void	env_copy(char **env, char **envp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		env[j] = ft_strdup(envp[i]);
		i++;
		j++;
	}
	env[j] = 0;
}

void	shell_lvl(char **env)
{
	int		i;
	char	*tmp;
	int		lvl;

	i = 0;
	while (env[i] && ft_strncmp("SHLVL=", env[i], 6))
		i++;
	if (!env[i])
		exit(1);
	tmp = env[i];
	lvl = ft_atoi(&tmp[6]);
	if (lvl < 0)
		lvl = 0;
	else
		lvl++;
	free(tmp);
	tmp = ft_itoa(lvl);
	env[i] = ft_strjoin("SHLVL=", tmp);
	free(tmp);
}
