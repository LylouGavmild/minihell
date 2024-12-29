/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:58 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:07:05 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_btree(t_Node *root)
{
	if (!root)
		return ;
	free_btree(root->left);
	free(root->token.value);
	free_btree(root->right);
	free(root);
}

int	btreeexpand3(char *str, char **re, int *len, t_Minishell *mini)
{
	char	*tmp2;
	char	*tmp;

	len[1] = 1;
	while (str[len[0] + len[1]] && (ft_isalnum(str[len[0] + len[1]])
			|| str[len[0] + len[1]] == '_'))
		len[1]++;
	tmp = malloc(sizeof(char) * (len[1]));
	if (!tmp)
		return (1);
	ft_strlcpy(tmp, &str[len[0] + 1], len[1]);
	tmp2 = expand(*(mini->envp), mini->noenv, tmp);
	free(tmp);
	if (!tmp2)
	{
		len[0] += len[1];
		return (0);
	}
	re[0] = ft_strjoin_w_free(re[0], tmp2);
	if (!re[0])
		return (free(tmp2), 1);
	len[2] += ft_strlen(tmp2);
	free(tmp2);
	len[0] += len[1];
	return (0);
}

char	*btreeexpand6(char *str, char *s, int *len, t_Minishell *mini)
{
	char	*re;

	re = splitjoin(s, str[len[0]]);
	len[0]++;
	len[2]++;
	while (str[len[0]] && str[len[0]] != '\"')
		btreeexpand5(str, &re, len, mini);
	if (str[len[0]] == '\"')
	{
		re = splitjoin(re, str[len[0]]);
		len[0]++;
		len[2]++;
	}
	return (re);
}
