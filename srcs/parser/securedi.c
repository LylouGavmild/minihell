/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   securedi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:23:53 by abutet            #+#    #+#             */
/*   Updated: 2024/12/02 15:49:21 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redisecu2(char *str, int *i)
{
	if (!i[0])
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &str[i[0]], mapchr(&str[i[0]]));
		return (write(2, "'\n", 2), 1);
	}
	i[0] += mapchr(&str[i[0]]);
	while (str[i[0]] && (is_whitespace(str[i[0]])
			|| str[i[0]] == '('))
		i[0]++;
	if (mapchr(&str[i[0]]) && str[i[0]] != '('
		&& str[i[0]] != '<' && str[i[0]] != '>')
	{
		write(2, "syntax error near unexpected token `", 36);
		write(2, &str[i[0]], mapchr(&str[i[0]]));
		return (write(2, "'\n", 2), 1);
	}
	return (0);
}

void	supthequote(char *str, int *i)
{
	int	j;

	j = 0;
	if ((str[i[0] + 1] == '"' || str[i[0] + 1] == '\'')
		&& (i[0] == 0 || str[i[0] - 1] != '$'))
	{
		while (str[i[0] + j])
		{
			str[i[0] + j] = str[i[0] + j + 1];
			j++;
		}
		str[i[0] + j] = '\0';
		i[0]--;
	}
}

int	redisecu3(char *str, int *i)
{
	if ((str[i[0]] == '|' && str[i[0] + 1] != '|')
		|| str[i[0]] == '>' || str[i[0]] == '<')
	{
		if (redisecup(str, i))
			return (1);
		i[0]--;
	}
	else if (mapchr(&str[i[0]]) && str[i[0]] != '(' && str[i[0]] != ')')
	{
		if (redisecu2(str, i))
			return (1);
		i[0]--;
	}
	return (0);
}

int	redisecu(char *str)
{
	int		i;
	char	c;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			c = str[i++];
			while (str[i] && str[i] != c)
				i++;
			if (!str[i])
				i--;
		}
		else if (str[i] == '$')
		{
			supthequote(str, &i);
			continue ;
		}
		else if (redisecu3(str, &i))
			return (1);
		if (!str[i])
			break ;
	}
	return (redisecupar(str));
}
