/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   securedi_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:23:53 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:01:43 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redisecupar4(char *str, int *j)
{
	char	c;

	if (str[j[0]] == '\'' || str[j[0]] == '\"')
	{
		if (j[0] > 0 && str[j[0] - 1] == '\\')
			return (2);
		c = str[j[0]++];
		while (str[j[0]] && str[j[0]] != c)
			j[0]++;
		if (!str[j[0]])
			j[0] -= 1;
		return (2);
	}
	return (0);
}

int	redisecup2(char *str, int *i)
{
	int	j;

	j = i[0] - 1;
	while (j > 0 && is_whitespace(str[j]))
		j--;
	while (j > 0 && mapchr(&str[j]))
		j--;
	if (!mapchr(&str[j]))
		j++;
	if (str[j] == ')')
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &str[i[0]], mapchr(&str[i[0]]));
		return (write(2, "'\n", 2), 1);
	}
	if (str[i[0]] == '|' && str[j] == '(')
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &str[i[0]], mapchr(&str[i[0]]));
		return (write(2, "'\n", 2), 1);
	}
	return (0);
}

int	redisecup(char *str, int *i)
{
	if (!i[0] && str[i[0]] == '|')
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &str[i[0]], mapchr(&str[i[0]]));
		return (write(2, "'\n", 2), 1);
	}
	else if (i[0])
	{
		if (redisecup2(str, i))
			return (1);
	}
	i[0] += mapchr(&str[i[0]]);
	while (str[i[0]] && is_whitespace(str[i[0]]))
		i[0]++;
	if (mapchr(&str[i[0]]))
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &str[i[0]], mapchr(&str[i[0]]));
		return (write(2, "'\n", 2), 1);
	}
	return (0);
}
