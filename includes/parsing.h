/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:29:14 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/26 11:55:47 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <bsd/string.h>
# include <unistd.h>

typedef enum TokenType
{
	TOKEN_OPERATOR,
	TOKEN_CMD,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_IDENTIFIER,
	TOKEN_END
}	t_TokenType;

typedef struct Token
{
	t_TokenType	type;
	char		*value;
}	t_Token;

typedef struct t_Lexer
{
	char	*input;
	size_t	pos;
	t_Token	current_token;
}	t_Lexer;

typedef struct Node
{
	t_Token			token;
	struct Node		*left;
	struct Node		*right;
}	t_Node;

int		mapchr(char *c);
int		ft_strncmp(char *s1, char *s2, size_t n);
void	free_btree(t_Node *root);
int		redisecu(char *str);
int		redisecupar(char *str);
int		redisecup(char *str, int *i);
int		redisecupar4(char *str, int *j);
void	lexer_init(t_Lexer *lexer, char *input);
t_Token	lexer_next_token(t_Lexer *lexer);
t_Node	*create_node(t_Token token);
t_Node	*parse_expression(t_Lexer *lexer);
t_Node	*parse_factor(t_Lexer *lexer);
t_Node	*parse_term0(t_Lexer *lexer);
t_Node	*parse_term1(t_Lexer *lexer);

#endif
