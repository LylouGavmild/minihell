/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_maker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:58 by abutet            #+#    #+#             */
/*   Updated: 2024/12/04 10:35:06 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	btree_cmd(t_Minishell *mini, t_Node *root)
{
	root->token.value = btreeexpand(root->token.value, mini);
	if (!root->token.value[0] || !only_white_space(root->token.value))
		return (0);
	mini->commande[mini->nbcmd].cmd = spesplit(root->token.value, mini);
	mini->commande[mini->nbcmd].in = 0;
	mini->commande[mini->nbcmd].out = 0;
	mini->nbcmd += 1;
	mini->nbcmdtmp += 1;
	mini->commande = ft_realloc(mini->commande, sizeof(t_temp) * mini->nbcmd,
			sizeof(t_temp) * (mini->nbcmd + 1));
	if (!mini->commande)
		exit(1);
	return (0);
}

int	btree_spipe(t_Minishell *mini, t_Node *root, int l)
{
	int	r;

	r = btree_if(mini, root->left, l);
	if (r)
		return (r);
	r = btree_if(mini, root->right, l);
	if (r)
		return (r);
	return (0);
}

int	btree_and(t_Minishell *mini, t_Node *root, int l)
{
	int	r;

	r = btree_if(mini, root->left, l);
	if (!r)
		return (btree_if(mini, root->right, l));
	else
		return (r);
}

int	btree_dpipe(t_Minishell *mini, t_Node *root, int l)
{
	int	r;

	r = btree_if(mini, root->left, l);
	if (!r)
		return (r);
	else
	{
		if (r == 130 || r == 131)
			return (r);
		return (btree_if(mini, root->right, l));
	}
}
