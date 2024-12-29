/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:59:52 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 14:24:44 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**splitwilds(char *pat, char ***sn)
{
	char	*cwd;
	char	**splited;
	char	**tmp;
	int		i[2];

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (sn[0]);
	splited = dirreader(cwd);
	if (!splited)
		(free(cwd), exit(1));
	triewilds(splited);
	tmp = malloc(sizeof(char **) * (ft_maplen(splited) + 1));
	if (!tmp)
		(free(cwd), free_map(tmp), exit(1));
	i[0] = -1;
	i[1] = 0;
	while (splited[++i[0]])
	{
		if (patern_finder(splited[i[0]], pat) && splited[i[0]][0] != '.')
			tmp[i[1]++] = splited[i[0]];
		else
			free(splited[i[0]]);
	}
	return (free(splited), free(cwd), tmp[i[1]] = NULL, tmp);
}

void	splitw_help0(char *str, int *start)
{
	while (start[0] && !is_whitespace(str[start[0]])
		&& !mapchr(&str[start[0]]))
	{
		if (str[start[0]] == '\'')
		{
			start[0] -= 1;
			while (start[0] && str[start[0]] != '\'')
				start[0] -= 1;
			if (str[start[0]] == '\'')
				start[0] -= 1;
			continue ;
		}
		if (str[start[0]] == '\"')
		{
			start[0] -= 1;
			while (start[0] && str[start[0]] != '\"')
				start[0] -= 1;
			if (str[start[0]] == '\"')
				start[0] -= 1;
			continue ;
		}
		start[0]--;
	}
	if (start[0])
		start[0]++;
}

char	*splitw_help1(char *str, int *start, char *pat)
{
	int	c;

	start[0]--;
	while (str[++start[0]] && !is_whitespace(str[start[0]])
		&& !mapchr(&str[start[0]]))
	{
		if (str[start[0]] == '\'' || str[start[0]] == '\"')
		{
			if (start[0] > 0 && str[start[0] - 1] == '\\')
			{
				pat = splitjoin(pat, str[start[0]]);
				continue ;
			}
			c = str[start[0]];
			while (str[++start[0]] && str[start[0]] != c)
				pat = splitjoin(pat, str[start[0]]);
			if (!str[start[0]])
				start[0] -= 1;
			continue ;
		}
		if (str[start[0]] != '\\')
			pat = splitjoin(pat, str[start[0]]);
	}
	return (pat);
}

char	**splitw(char *str, char ***sn, int *j, int *start)
{
	char	*pat;
	char	**tmp;

	pat = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!pat)
		exit(1);
	pat[0] = '\0';
	splitw_help0(str, start);
	pat = splitw_help1(str, start, pat);
	tmp = splitwilds(pat, sn);
	if (maplen(tmp) > 0)
	{
		if (sn[0][j[0]])
			free(sn[0][j[0]]);
		sn[0][j[0]] = NULL;
		sn[0] = malloc_resize(sn[0], tmp, str);
		j[0] += maplen(tmp) - 1;
	}
	else
	{
		if (sn[0][j[0]])
			free(sn[0][j[0]]);
		sn[0][j[0]] = ft_strdup(pat);
	}
	return (free(pat), free(tmp), sn[0]);
}
