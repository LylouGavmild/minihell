/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   securedirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:58 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:33:46 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*securiser(char *str, char *tmp, int i)
{
	char	*r;
	int		j;
	int		h;

	r = malloc(sizeof(char) * (ft_strlen(str) + 3));
	if (!r)
		return (NULL);
	j = -1;
	while (++j < i)
		r[j] = str[j];
	r[j++] = '\'';
	h = -1;
	while (tmp[++h])
	{
		r[j] = str[j - 1];
		j++;
	}
	r[j] = '\'';
	while (str[++j - 2])
		r[j] = str[j - 2];
	r[j] = '\0';
	return (free(str), r);
}

int	securedirect_micro(t_Minishell *mini, char **str, char *cp, int *i)
{
	char	*tmp;
	char	*tmp1;

	i[1] = 1;
	while (cp[i[0] + i[1]] && (ft_isalnum(cp[i[0] + i[1]])
			|| cp[i[0] + i[1]] == '_'))
		i[1]++;
	tmp = malloc(sizeof(char) * (i[1]));
	if (!tmp)
		exit(1);
	ft_strlcpy(tmp, &cp[i[0] + 1], i[1]);
	tmp1 = expand(*(mini->envp), mini->noenv, tmp);
	free(tmp);
	if (!tmp1)
		return (i[1]);
	if (as_one_white_space(tmp1))
		*str = securiser(*str, tmp1, i[0]);
	return (free(tmp1), 0);
}

int	securedirect_helper(char *cp, int *i, int *j)
{
	char	c;

	if (is_whitespace(cp[i[0]]))
	{
		if (j[1])
			return (free(cp), 2);
		return (1);
	}
	if (cp[i[0]] == '"' || cp[i[0]] == '\'')
	{
		c = cp[i[0]++];
		while (cp[i[0]] && cp[i[0]] != c)
			i[0]++;
		if (!cp[i[0]])
			i[0]--;
		return (1);
	}
	return (0);
}

static void	help(t_Minishell *mini, int *i, int *j, char **str)
{
	str[0] = btreeexpand(str[0], mini);
	i[0] = -1;
	j[0] = 0;
	j[1] = 0;
}

char	*securedirect(t_Minishell *mini, char *str)
{
	char	*cp;
	int		r;
	int		i[2];
	int		j[2];

	cp = ft_strdup(str);
	help(mini, i, j, &str);
	while (cp[++i[0]])
	{
		r = securedirect_helper(cp, i, j);
		if (r == 1)
			continue ;
		if (r == 2)
			return (str);
		if (cp[i[0]] == '$')
		{
			r = securedirect_micro(mini, &str, cp, i);
			if (!r)
				return (free(cp), str);
			i[0] += r - 1;
			continue ;
		}
		j[1] = 1;
	}
	return (free(cp), str);
}
