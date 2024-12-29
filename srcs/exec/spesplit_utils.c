/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spesplit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:00:56 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:18:22 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*splitjoin(char *s1, char c)
{
	char	*sj;
	int		n;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		return (ft_strdup(&c));
	n = ft_strlen(s1);
	sj = (char *)malloc((sizeof(char) * n) + 2);
	if (!sj)
		exit(1);
	while (s1[i] != '\0')
		sj[j++] = s1[i++];
	i = 0;
	if (c != '\0')
		sj[j++] = c;
	sj[j] = '\0';
	free(s1);
	return (sj);
}

void	expandq(t_Minishell *mini, char **sn, int *i)
{
	char	*tmp;
	char	*tmp2;

	tmp = sn[i[1]];
	tmp2 = ft_itoa(mini->exit_code);
	if (sn[i[1]])
		sn[i[1]] = ft_strjoin(tmp, tmp2);
	else
		sn[i[1]] = ft_strdup(tmp2);
	free(tmp);
	free(tmp2);
}

int	splitexpand(char *s, char **sn, int *i, t_Minishell *mini)
{
	if (s[*i] != '$' || !s[*i + 1])
		return (0);
	if (s[*i + 1] == '?')
		return (expandq(mini, sn, i), 1);
	return (0);
}

int	splitslash(char *s, char **sn, int *i, int j)
{
	if (s[*i] != '\\')
		return (0);
	*i += 1;
	if (!s[*i])
		return (1);
	sn[j] = splitjoin(sn[j], s[*i]);
	*i += 1;
	return (1);
}

void	spesplit4(char *s, char **sn, int *i)
{
	int	r;

	r = *i;
	*i += 1;
	while (s[*i] && s[*i] != '\'')
	{
		sn[i[1]] = splitjoin(sn[i[1]], s[*i]);
		*i += 1;
	}
	if (s[*i] == '\'')
		*i += 1;
	if (*i - r < 3)
		sn[i[1]] = splitjoin(sn[i[1]], '\0');
}
