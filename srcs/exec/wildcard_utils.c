/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:59:52 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:14:51 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**dirreader(char *cwd)
{
	struct dirent	*dirptr;
	DIR				*d_read;
	DIR				*d_move;
	char			**test;
	int				i;

	test = NULL;
	i = 0;
	dirptr = 0;
	d_read = opendir(cwd);
	d_move = opendir(cwd);
	if (d_read == 0 || d_move == 0)
		write(2, "Error: d_read: can't opendir\n", 29);
	else
	{
		while (readdir(d_move))
		{
			dirptr = readdir(d_read);
			test = ft_realloc(test, sizeof(char **) * (i + 1),
					sizeof(char **) * (i + 2));
			test[i++] = strdup(dirptr->d_name);
			test[i] = NULL;
		}
	}
	return (closedir(d_read), closedir(d_move), test);
}

void	patern_finder_helper0(size_t *i, size_t *j, char *str, char *patern)
{
	while (patern[*j] == '*' && *j + 1 <= ft_strlen(patern) && str[*i])
	{
		if (patern[*j + 1] == '*')
		{
			*j += 1;
			continue ;
		}
		if (patern[*j + 1] == str[*i])
		{
			*j += 1;
			break ;
		}
		*i += 1;
	}
}

void	patern_finder_helper1(size_t *i, size_t *j, char *str, char *patern)
{
	while (str[*i])
	{
		patern_finder_helper0(i, j, str, patern);
		if (!patern[*j] && str[*i])
		{
			if (*j && patern[*j - 1] == str[strlen(str) - 1])
			{
				*i = strlen(str);
				break ;
			}
			return ;
		}
		if (patern[*j] == str[*i])
		{
			if (patern[*j])
				*j += 1;
			*i += 1;
			continue ;
		}
		break ;
	}
}

int	patern_finder(char *str, char *patern)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	patern_finder_helper1(&i, &j, str, patern);
	while (patern[j] == '*')
		j++;
	if (j != strlen(patern))
		return (0);
	if (i != strlen(str))
		return (0);
	return (1);
}

char	**malloc_resize(char **map1, char **map2, char *str)
{
	char	**mapr;
	int		len;
	int		i;

	len = ft_maplen(map1) + ft_maplen(map2) + strlenmal(str) + 1;
	mapr = malloc(sizeof(char *) * (len));
	if (!mapr)
		exit(1);
	len = 0;
	while (map1[len])
	{
		mapr[len] = map1[len];
		len++;
	}
	i = 0;
	while (map2[i])
	{
		mapr[len + i] = map2[i];
		i++;
	}
	mapr[len + i] = NULL;
	free (map1);
	return (mapr);
}
