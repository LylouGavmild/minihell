/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 13:02:21 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:21:52 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

size_t	ft_strlen_free(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (free(str), i);
}

char	*expand(char **env, char **noenv, char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_strjoin(str, "=");
	if (env && key)
	{
		while (env[i])
		{
			if (!ft_strncmp(env[i], key, ft_strlen(key)))
				return (ft_strdup(&env[i][ft_strlen_free(key)]));
			i++;
		}
		i = 0;
	}
	if (noenv && key)
	{
		while (noenv[i])
		{
			if (!ft_strncmp(noenv[i], key, ft_strlen(key)))
				return (ft_strdup(&noenv[i][ft_strlen_free(key)]));
			i++;
		}
	}
	return (free(key), NULL);
}
