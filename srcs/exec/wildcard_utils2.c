/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:59:52 by abutet            #+#    #+#             */
/*   Updated: 2024/11/21 10:26:45 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	trieswap(char **str, int *i, int t)
{
	char	*tmp;

	if (t < 0)
	{
		tmp = str[i[0]];
		str[i[0]] = str[i[1]];
		str[i[1]] = tmp;
	}
}

void	majtrie(char **str, int *i)
{
	int	j;

	j = 0;
	while (str[i[0]][j] == str[i[1]][j])
		j++;
	trieswap(str, i, str[i[0]][j] - str[i[1]][j]);
}

void	triewilds1(char **str, int *i)
{
	int	m;
	int	j;

	m = 0;
	if (str[i[0]][0] >= 65 && str[i[0]][0] <= 90)
		m += 32;
	if (str[i[1]][0] >= 65 && str[i[1]][0] <= 90)
		m -= 32;
	j = 0;
	while (str[i[0]][j] && (str[i[0]][j] + m) == str[i[1]][j])
	{
		j++;
		m = 0;
		if (str[i[0]][j] >= 65 && str[i[0]][j] <= 90)
			m += 32;
		if (str[i[1]][j] >= 65 && str[i[1]][j] <= 90)
			m -= 32;
	}
	if (!str[i[0]][j] && str[i[0]][j] == str[i[1]][j])
		majtrie(str, i);
	else
		trieswap(str, i, str[i[1]][j] - str[i[0]][j] - m);
}

void	triewilds(char **str)
{
	int	i[2];

	i[0] = -1;
	while (str[++i[0]])
	{
		i[1] = i[0];
		while (str[++i[1]])
			triewilds1(str, i);
	}
}
