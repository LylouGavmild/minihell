/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:58 by abutet            #+#    #+#             */
/*   Updated: 2024/12/04 10:34:55 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*btreeexpand2(char *str, char *s, int *len)
{
	char	*re;

	re = splitjoin(s, str[len[0]]);
	if (!re)
		exit(1);
	len[0]++;
	len[2]++;
	while (str[len[0]] && str[len[0]] != '\'')
	{
		re = splitjoin(re, str[len[0]]);
		if (!re)
			exit(1);
		len[0]++;
		len[2]++;
	}
	if (str[len[0]] == '\'')
	{
		re = splitjoin(re, str[len[0]]);
		if (!re)
			exit(1);
		len[0]++;
		len[2]++;
	}
	return (re);
}

int	btreeexpand4(char *str, char **re, int *len)
{
	char	*tmp;

	tmp = ft_substr(str, len[0], 1);
	if (!tmp)
		return (1);
	re[0] = ft_strjoin_w_free(re[0], tmp);
	if (!re[0])
		return (free(tmp), 1);
	free(tmp);
	len[0]++;
	len[2]++;
	re[0][len[2]] = '\0';
	return (0);
}

int	btreeexpand5(char *str, char **re, int *len, t_Minishell *mini)
{
	if (str[len[0]] == '$'
		&& (ft_isalnum(str[len[0] + 1]) || str[len[0] + 1] == '*'))
	{
		if (len[0] > 0 && str[len[0] - 1] == '\\')
			return (1);
		if (btreeexpand3(str, re, len, mini))
			return (1);
		return (0);
	}
	if (btreeexpand4(str, re, len))
		return (1);
	return (0);
}

char	*btreeexpand(char *str, t_Minishell *mini)
{
	int		len[3];
	char	*re;

	len[0] = 0;
	len[2] = 0;
	re = malloc(sizeof(char));
	if (!re)
		exit(1);
	re[0] = '\0';
	while (str[len[0]])
	{
		if (str[len[0]] == '"')
		{
			re = btreeexpand6(str, re, len, mini);
			continue ;
		}
		if (str[len[0]] == '\'')
		{
			re = btreeexpand2(str, re, len);
			continue ;
		}
		if (btreeexpand5(str, &re, len, mini))
			return (free(re), str);
	}
	return (re[len[2]] = '\0', free(str), re);
}

int	btree_main(char *input, t_Minishell *mini)
{
	int			x;
	t_Lexer		lexer;
	t_Node		*root;

	if (redisecu(input))
		return (free(input), 2);
	lexer_init(&lexer, input);
	root = parse_expression(&lexer);
	if (!root)
		return (free(input), 2);
	mini->commande = malloc(sizeof(t_temp));
	if (!mini->commande)
		return (free(input), 1);
	mini->nbcmd = 0;
	mini->origine = root;
	free(input);
	mini->nbcmdtmp = 0;
	x = btree_if(mini, root, -1);
	if (g_signret != 130 && x != 130)
		free(mini->commande);
	free_btree(root);
	return (x);
}
