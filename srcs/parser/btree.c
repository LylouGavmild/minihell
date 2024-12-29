/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:25:10 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/26 10:22:15 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_Node	*parse_term2_helper(t_Lexer *lexer, t_Node *node, t_Node *new_node)
{
	if (mapchr(new_node->token.value))
		lexer->pos -= mapchr(new_node->token.value);
	else
		lexer->pos--;
	return (free(new_node->token.value), free(new_node), node);
}

int	parse_term2_micro(t_Lexer *lexer, t_Node **node, t_Token *token)
{
	node[0] = parse_factor(lexer);
	if (!node[0])
		return (1);
	token[0] = lexer_next_token(lexer);
	return (0);
}

t_Node	*parse_term2(t_Lexer *lexer)
{
	t_Node	*node;
	t_Node	*new_node;
	t_Token	token;

	if (parse_term2_micro(lexer, &node, &token))
		return (NULL);
	while (token.type == TOKEN_CMD)
	{
		node->right = create_node(token);
		if (!ft_strncmp(node->token.value, ">", 1)
			|| !ft_strncmp(node->token.value, "<", 1))
			return (node);
		new_node = parse_factor(lexer);
		if (!new_node)
			return (free(node->right->token.value),
				free(node->right), free(node->token.value), free(node), NULL);
		if (new_node->token.type == TOKEN_OPERATOR)
			return (parse_term2_helper(lexer, node, new_node));
		node->right = new_node;
		token = lexer_next_token(lexer);
	}
	if (mapchr(token.value) || lexer->pos--)
		lexer->pos -= mapchr(token.value);
	return (free(token.value), node);
}

t_Node	*parse_term1(t_Lexer *lexer)
{
	t_Node	*node;
	t_Node	*new_node;
	t_Token	token;

	node = parse_term2(lexer);
	if (!node)
		return (NULL);
	token = lexer_next_token(lexer);
	while (token.type == TOKEN_OPERATOR && (token.value[0] == '<'
			|| token.value[0] == '>'))
	{
		new_node = create_node(token);
		new_node->left = node;
		new_node->right = parse_term2(lexer);
		if (!new_node->right)
			return (free_btree(new_node), NULL);
		node = new_node;
		token = lexer_next_token(lexer);
	}
	if (mapchr(token.value))
		lexer->pos -= mapchr(token.value);
	else
		lexer->pos--;
	free(token.value);
	return (node);
}

t_Node	*parse_term0(t_Lexer *lexer)
{
	t_Node	*node;
	t_Node	*new_node;
	t_Token	token;

	node = parse_term1(lexer);
	if (!node)
		return (NULL);
	token = lexer_next_token(lexer);
	while (token.type == TOKEN_OPERATOR
		&& (token.value[0] == '|' && token.value[1] == '\0'))
	{
		new_node = create_node(token);
		new_node->left = node;
		new_node->right = parse_term1(lexer);
		if (!new_node->right)
			return (free_btree(new_node), NULL);
		node = new_node;
		token = lexer_next_token(lexer);
	}
	if (mapchr(token.value))
		lexer->pos -= mapchr(token.value);
	else
		lexer->pos--;
	free(token.value);
	return (node);
}
