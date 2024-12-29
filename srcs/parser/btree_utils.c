/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:38:47 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/27 10:44:28 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_Node	*create_node(t_Token token)
{
	t_Node	*node;

	node = malloc(sizeof(t_Node));
	if (!node)
		exit (1);
	node->token = token;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_Node	*parse_factor(t_Lexer *lexer)
{
	t_Token	token;
	t_Node	*node;
	t_Token	t;

	token = lexer_next_token(lexer);
	if (token.type == TOKEN_CMD || token.type == TOKEN_OPERATOR
		|| token.type == TOKEN_RPAREN)
		return (create_node(token));
	else if (token.type == TOKEN_LPAREN)
	{
		node = parse_expression(lexer);
		if (!node)
			return (free(token.value), NULL);
		t = lexer_next_token(lexer);
		if (t.type != TOKEN_RPAREN)
		{
			write(2, "minishell: expect to close parenthesis\n", 39);
			return (free(t.value), free(token.value), NULL);
		}
		return (free(t.value), free(token.value), node);
	}
	write(2, "syntax error near unexpected token `newline'\n", 46);
	return (free(token.value), NULL);
}

t_Node	*parse_expression(t_Lexer *lexer)
{
	t_Node	*node;
	t_Node	*new_node;
	t_Token	token;

	node = parse_term0(lexer);
	if (!node)
		return (NULL);
	token = lexer_next_token(lexer);
	while (token.type == TOKEN_OPERATOR && (!ft_strncmp("||", token.value, 3)
			|| !ft_strncmp("&&", token.value, 3)))
	{
		new_node = create_node(token);
		new_node->left = node;
		new_node->right = parse_term0(lexer);
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
