/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:28:36 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/29 10:12:34 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	as_one_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_whitespace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*ft_memcpy(void *dest, void *src, size_t n)
{
	char	*sr;
	char	*ds;

	sr = (char *)src;
	ds = (char *)dest;
	if (!src && !dest)
		return (0);
	while (n--)
		*ds++ = *sr++;
	return (dest);
}

size_t	ft_strlcpy(char *dst, char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(src);
	if (!dst || !src)
		return (0);
	if (size)
	{
		if (i >= size)
			j = size - 1;
		else
			j = i;
		ft_memcpy(dst, src, j);
		dst[j] = '\0';
	}
	return (i);
}

char	*ft_strjoin_w_free(char *s1, char *s2)
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
	if (!s1 || !s2)
		return (NULL);
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

int	maplen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
