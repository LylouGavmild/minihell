/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_maker_if.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:58 by abutet            #+#    #+#             */
/*   Updated: 2024/12/04 10:40:06 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	btree_reif_help(t_Minishell *mini, t_Node *root, char **redirect)
{
	if (!ft_strncmp(root->token.value, ">", 1)
		&& mini->commande[mini->nbcmd - 1].out > 0)
		close(mini->commande[mini->nbcmd - 1].out);
	if (!ft_strncmp(root->token.value, "<", 1)
		&& mini->commande[mini->nbcmd - 1].in > 1)
		close(mini->commande[mini->nbcmd - 1].in);
	if (!ft_strncmp(root->token.value, ">>", 2))
		return (mini->commande[mini->nbcmd - 1].out = open(*redirect,
				O_APPEND | O_CREAT | O_WRONLY, 0644));
	else if (!ft_strncmp(root->token.value, "<<", 2))
	{
		mini->commande[mini->nbcmd - 1].in = here_doc(redirect, mini);
		if (mini->commande[mini->nbcmd - 1].in == -130)
			return (mini->commande[mini->nbcmd - 1].in = -1,
				set_signal_action(), g_signret = 130, 1);
		return (1);
	}
	else if (!ft_strncmp(root->token.value, ">", 1))
		return (mini->commande[mini->nbcmd - 1].out = open(*redirect,
				O_TRUNC | O_CREAT | O_WRONLY, 0644));
	else if (!ft_strncmp(root->token.value, "<", 1))
		return (mini->commande[mini->nbcmd - 1].in = open(*redirect,
				O_RDONLY, 0644));
	return (1);
}

int	btree_reif(t_Minishell *mini, t_Node *root, char **redirect)
{
	if (!(mini->commande[mini->nbcmd - 1].in))
		mini->commande[mini->nbcmd - 1].in = 0;
	if (!(mini->commande[mini->nbcmd - 1].out))
		mini->commande[mini->nbcmd - 1].out = 0;
	mini->nbcmdtmp++;
	if (btree_reif_help(mini, root, redirect) < 0)
	{
		if (g_signret != 130)
			return (write(2, "minishell: ", 11),
				write(2, *redirect, ft_strlen(*redirect)),
				write(2, ": no such file or directory\n", 28), 1);
		return (mini->exit_code = 130);
	}
	return (0);
}

int	btree_if3(t_Minishell *mini, int l, int r)
{
	if (g_signret == 130)
		return (free_cmd(mini->nbcmd - 1, mini->commande), g_signret = 0, 130);
	if (!l && r != 130)
	{
		if (mini->nbcmdtmp != 0 && !r)
			(fd_distri(mini->commande, mini->nbcmd), r = cmd(mini));
		while (l < mini->nbcmd)
			(free_map(mini->commande[l].cmd), l++);
		if (mini->nbcmdtmp == 0)
			close_all(mini->commande, mini->nbcmd);
		if (r == 4)
			(close_all(mini->commande, mini->nbcmd), r = 1);
		(free(mini->commande), mini->commande = malloc(sizeof(t_temp)));
		if (!mini->commande)
			exit(1);
		if (r == 130)
			free(mini->commande);
		l = -1;
		mini->nbcmd = 0;
		if (mini->nbcmdtmp == 0 && r == 3)
			return (0);
		mini->nbcmdtmp = 0;
	}
	return (r);
}

int	btree_if2(t_Minishell *mini, t_Node *root, int l)
{
	int	r;

	r = 0;
	if (root->token.type == TOKEN_OPERATOR
		&& !ft_strncmp("||", root->token.value, 2))
		r = btree_dpipe(mini, root, l);
	else if (root->token.type == TOKEN_OPERATOR
		&& !ft_strncmp("&&", root->token.value, 2))
		r = btree_and(mini, root, l);
	else if (root->token.type == TOKEN_OPERATOR
		&& !ft_strncmp("|", root->token.value, 2))
		r = btree_spipe(mini, root, ++l);
	else if (root->token.type == TOKEN_OPERATOR
		&& (!ft_strncmp(">", root->token.value, 2)
			|| !ft_strncmp("<", root->token.value, 2)
			|| !ft_strncmp(">>", root->token.value, 2)
			|| !ft_strncmp("<<", root->token.value, 2)))
		r = btree_redirect(mini, root, ++l, r);
	else if (root->token.type == TOKEN_CMD && ++l >= 0)
	{
		r = btree_cmd(mini, root);
		if (r)
			l--;
	}
	return (r = btree_if3(mini, l, r));
}

int	btree_if(t_Minishell *mini, t_Node *root, int l)
{
	if (!root)
		return (1);
	return (btree_if2(mini, root, l));
}
