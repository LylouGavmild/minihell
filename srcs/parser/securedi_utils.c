/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   securedi_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:23:53 by abutet            #+#    #+#             */
/*   Updated: 2024/11/26 10:30:43 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	rparou(char *str, int *t, int *p, int e)
{
	if (t[0])
	{
		if (mapchr(&str[e]))
			return (write(2, "syntax error near unexpected token `", 37),
				write(2, &str[e], t[0] - e), write(2, "'\n", 3), 1);
		return (write(2, "syntax error near unexpected token `('\n", 39), 1);
	}
	t[1] = 0;
	p[0] += 1;
	return (0);
}

void	rcmd(char *str, int *t, int *e, int *j)
{
	e[0] = j[0];
	while (str[j[0]] && !is_whitespace(str[j[0]]) && !mapchr(&str[j[0]]))
		j[0]++;
	t[0] = j[0]--;
	t[1] = 1;
}

int	redisecupar3(char *str, int *j, int *t, int *p)
{
	if (redisecupar4(str, j))
		return (2);
	if (is_whitespace(str[j[0]]))
		return (2);
	if (mapchr(&str[j[0]]) && str[j[0]] != '(' && str[j[0]] != ')')
	{
		t[0] = 0;
		t[1] = 1;
		j[0] += mapchr(&str[j[0]]) - 1;
		return (2);
	}
	if (str[j[0]] == ')')
	{
		if (!p[0] || !t[1])
			return (write(2,
					"syntax error near unexpected token `)'\n", 40), 1);
		p[0] -= 1;
		return (2);
	}
	return (0);
}

int	redisecupar2(char *str, int j, int *t, int *p)
{
	int	e;
	int	r;

	e = 0;
	while (str[++j])
	{
		r = redisecupar3(str, &j, t, p);
		if (r == 1)
			return (1);
		if (r == 2)
			continue ;
		if (str[j] == '(')
		{
			if (rparou(str, t, p, e))
				return (1);
			continue ;
		}
		rcmd(str, t, &e, &j);
	}
	return (0);
}

int	redisecupar(char *str)
{
	int	j;
	int	t[2];
	int	p;

	j = -1;
	t[0] = 0;
	t[1] = 0;
	p = 0;
	if (redisecupar2(str, j, t, &p))
		return (1);
	if (p)
		return (write(2,
				"syntax error aaa near unexpected token `newline'\n", 50), 1);
	return (0);
}
