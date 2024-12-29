/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_maker_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:58 by abutet            #+#    #+#             */
/*   Updated: 2024/12/02 15:47:57 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	btree_file3(t_Minishell *mini, t_Node *root, char **re)
{
	mini->commande[mini->nbcmd].cmd = malloc(sizeof(char *) * 2);
	mini->commande[mini->nbcmd].cmd[0] = ft_strdup("\0");
	mini->commande[mini->nbcmd].cmd[1] = NULL;
	mini->commande[mini->nbcmd].in = 0;
	mini->commande[mini->nbcmd++].out = 0;
	mini->commande = ft_realloc(mini->commande, sizeof(t_temp) * mini->nbcmd,
			sizeof(t_temp) * (mini->nbcmd + 1));
	btree_reif(mini, root, re);
	mini->nbcmdtmp--;
	free_map(re);
	return (3);
}

int	btree_file2alt(t_Minishell *mini, t_Node *root, char **re)
{
	if (btree_reif(mini, root, re))
		return (free_map(re), 1);
	if (re[1])
	{
		if (!mini->commande[mini->nbcmd - 1].cmd
			|| !mini->commande[mini->nbcmd - 1].cmd[0])
			mini->commande[mini->nbcmd - 1].cmd
				= malloc_fus(mini->commande[mini->nbcmd - 1].cmd, &re[1]);
		else
		{
			if (mini->commande[mini->nbcmd - 1].cmd)
			{
				free(mini->commande[mini->nbcmd - 1].cmd[0]);
				free(mini->commande[mini->nbcmd - 1].cmd);
			}
			mini->commande[mini->nbcmd - 1].cmd = mapcp(&re[1]);
			return (free_map(re), 0);
		}
	}
	return (free(re[0]), free(re), 0);
}

int	btree_file2(t_Minishell *mini, t_Node *root, char **re, int i)
{
	int	r;

	if (i == 3)
		return (btree_file2alt(mini, root, re));
	mini->commande[mini->nbcmd].cmd = mapcp(&re[1]);
	mini->commande[mini->nbcmd].in = 0;
	mini->commande[mini->nbcmd].out = 0;
	mini->nbcmd += 1;
	mini->commande = ft_realloc(mini->commande, sizeof(t_temp) * mini->nbcmd,
			sizeof(t_temp) * (mini->nbcmd + 1));
	r = btree_reif(mini, root, re);
	free_map(re);
	return (r);
}

int	btree_file(t_Minishell *mini, t_Node *root, int i)
{
	char	**re;

	if (!root || !root->right)
		return (1);
	root->right->token.value = securedirect(mini, root->right->token.value);
	if (!root->right->token.value || !root->right->token.value[0]
		|| !only_white_space(root->right->token.value))
		return (write(2, "ambiguous redirect\n", 19), 4);
	if (!i || i == 4)
		return (btree_file_helper(mini, root));
	else
	{
		re = spesplit(root->right->token.value, mini);
		if (!re[1])
			return (btree_file3(mini, root, re));
		else
			return (btree_file2(mini, root, re, i));
	}
	return (0);
}

int	btree_redirect(t_Minishell *mini, t_Node *root, int l, int r)
{
	if (!(root))
		return (1);
	r = btree_if(mini, root->left, l);
	if (r == 4 || r == 130)
		return (r);
	return (btree_file(mini, root, r));
}
