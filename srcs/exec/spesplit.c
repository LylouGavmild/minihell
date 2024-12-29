/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spesplit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:00:56 by abutet            #+#    #+#             */
/*   Updated: 2024/11/18 09:33:38 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	spesplit3(char *s, char **sn, int *i, t_Minishell *mini)
{
	int	x;
	int	r;

	r = *i;
	*i += 1;
	while (s[*i] && s[*i] != '"')
	{
		if (splitslash(s, sn, i, i[1]))
			continue ;
		x = splitexpand(s, sn, i, mini);
		if (x == -1)
		{
			*i += 1;
			while (s[*i] && ft_isalnum(s[*i]))
				*i += 1;
		}
		*i += x;
		if (!x)
			sn[i[1]] = splitjoin(sn[i[1]], s[*i]);
		*i += 1;
	}
	if (s[*i] == '"')
		*i += 1;
	if (*i - r < 3)
		sn[i[1]] = splitjoin(sn[i[1]], '\0');
}

int	spesplit2_help(char *s, char **sn, int *i, t_Minishell *mini)
{
	int	x;

	if (splitslash(s, sn, i, i[1]))
		return (i[0]--, 1);
	x = splitexpand(s, sn, i, mini);
	if (x == -1)
	{
		*i += 1;
		while (s[*i] && ft_isalnum(s[*i]))
			*i += 1;
		return (-1);
	}
	*i += x;
	if (x)
		return (1);
	return (0);
}

int	spesplit2_help2(char *s, char ***sn, int *i, t_Minishell *mini)
{
	if (s[*i] == '*')
	{
		sn[0] = splitw(s, sn, &i[1], &i[0]);
		return (1);
	}
	if (s[*i] == '"')
	{
		spesplit3(s, sn[0], i, mini);
		return (1);
	}
	if (s[*i] == '\'')
	{
		spesplit4(s, sn[0], i);
		return (1);
	}
	snjoin(s, sn, i);
	if (s[*i])
		*i += 1;
	return (1);
}

int	spesplit2(char *s, char ***sn, int *i, t_Minishell *mini)
{
	int	x;

	while (s[*i] && !is_whitespace(s[*i]))
	{
		x = spesplit2_help(s, sn[0], i, mini);
		if (x == -1)
			return (0);
		if (x && i[0]++)
			continue ;
		spesplit2_help2(s, sn, i, mini);
	}
	return (1);
}

char	**spesplit(char *s, t_Minishell *mini)
{
	char	***sn;
	char	**tmp;
	int		i[2];

	i[0] = 0;
	i[1] = 0;
	sn = malloc(sizeof(char **) * 2);
	if (!sn)
		exit(1);
	sn[0] = malloc(sizeof(char *) * (strlenmal(s) + 1));
	if (!sn[0])
		exit(1);
	sn[0][0] = NULL;
	sn[1] = NULL;
	while (s[i[0]])
	{
		if (!is_whitespace(s[i[0]]))
		{
			sn[0][i[1]] = NULL;
			i[1] += spesplit2(s, sn, i, mini);
		}
		if (s[i[0]])
			i[0]++;
	}
	return (sn[0][i[1]] = 0, tmp = sn[0], free(sn), tmp);
}
