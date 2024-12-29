/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:01:05 by abutet            #+#    #+#             */
/*   Updated: 2024/11/18 15:09:10 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*joinpwd(char *s1, char *s2)
{
	char	*sj;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	if (!s2)
		return (s1);
	sj = malloc(sizeof(char) * (strlen(s1) + strlen(s2)) + 1);
	if (!sj)
		return (NULL);
	while (s1[++i])
		sj[i] = s1[i];
	while (s2[j])
		sj[i++] = s2[j++];
	sj[i] = '\0';
	return (free(s1), sj);
}

int	st_pwd(char *key, char **env)
{
	int		i;

	i = 0;
	while (env[i] && ft_strncmp(key, env[i], 4))
		i++;
	if (!env[i])
		i = -1;
	return (i);
}

char	**set_pwd(char *pwd, char ***env, int b)
{
	int		i;
	char	*key;

	if (b)
	{
		key = ft_strdup("PWD=");
		i = st_pwd(key, *env);
	}
	else
	{
		key = ft_strdup("OLDPWD=");
		i = st_pwd(key, *env);
	}
	if (i == -1)
	{
		i = maplen(env[0]) + 1;
		env[0] = (char **)ft_realloc((void *)env[0], sizeof(char **) * i,
				sizeof(char **) * (i + 1));
		env[0][i] = NULL;
		i--;
	}
	else
		free(env[0][i]);
	env[0][i] = joinpwd(key, pwd);
	return (free(pwd), env[0]);
}
