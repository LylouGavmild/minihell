/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:34:16 by abutet            #+#    #+#             */
/*   Updated: 2024/11/19 10:37:31 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	unset2(char **env, char **noenv, char *key)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
		{
			free(env[i]);
			while (env[i++])
				env[i - 1] = env[i];
			break ;
		}
	}
	i = -1;
	while (noenv[++i])
	{
		if (!ft_strncmp(noenv[i], key, ft_strlen(key)))
		{
			free(noenv[i]);
			while (noenv[i++])
				noenv[i - 1] = noenv[i];
			break ;
		}
	}
}

int	unset(char **env, char **noenv, t_temp *commande)
{
	int	i;

	i = 0;
	while (commande->cmd[++i])
		unset2(env, noenv, commande->cmd[i]);
	return (0);
}
