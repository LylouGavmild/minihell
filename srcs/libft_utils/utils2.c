/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 10:30:10 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/29 10:12:52 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_whitespace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

size_t	strlenmal(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (!is_whitespace(*s))
		{
			i++;
			while (*s && !is_whitespace(*s))
				s++;
		}
		else
			s++;
	}
	return (i);
}

char	**ft_split2(char *s)
{
	char		**sn;
	size_t		i;
	size_t		j;

	if (!s)
		return (0);
	i = 0;
	sn = malloc(sizeof(char *) * (strlenmal(s) + 1));
	if (!sn)
		return (0);
	while (*s)
	{
		if (!is_whitespace(*s))
		{
			j = 0;
			while (*s && !is_whitespace(*s) && ++j)
				s++;
			sn[i++] = ft_substr(s - j, 0, j);
		}
		else
			s++;
	}
	sn[i] = 0;
	return (sn);
}
