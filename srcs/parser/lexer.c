/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-rese <ade-rese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 13:21:56 by ade-rese          #+#    #+#             */
/*   Updated: 2024/07/25 13:21:56 by ade-rese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_Token	lexer_next_helper3(t_Lexer *lexer, char *input)
{
	ft_strlcpy(lexer->current_token.value,
		&input[lexer->pos], mapchr(&input[lexer->pos]) + 1);
	lexer->current_token.type = TOKEN_OPERATOR;
	lexer->pos += mapchr(&input[lexer->pos]);
	return (lexer->current_token);
}

t_Token	lexer_next_helper2(t_Lexer *lexer)
{
	lexer->current_token.value[0] = ')';
	lexer->current_token.value[1] = '\0';
	lexer->current_token.type = TOKEN_RPAREN;
	lexer->pos++;
	return (lexer->current_token);
}

t_Token	lexer_next_helper1(t_Lexer *lexer)
{
	lexer->current_token.value[0] = '(';
	lexer->current_token.value[1] = '\0';
	lexer->current_token.type = TOKEN_LPAREN;
	lexer->pos++;
	return (lexer->current_token);
}

t_Token	lexer_next_helper0(t_Lexer *lexer, char *input, size_t length)
{
	char	c;
	size_t	start;

	start = lexer->pos;
	while (input[lexer->pos] && !mapchr(&input[lexer->pos]))
	{
		if (input[lexer->pos] == '"' || input[lexer->pos] == '\'')
		{
			c = input[lexer->pos];
			lexer->pos++;
			while (input[lexer->pos] && input[lexer->pos] != c)
				lexer->pos++;
			if (input[lexer->pos])
				lexer->pos++;
			continue ;
		}
		lexer->pos++;
	}
	length = lexer->pos - start;
	ft_strlcpy(lexer->current_token.value, &input[start], length + 1);
	lexer->current_token.value[length] = '\0';
	lexer->current_token.type = TOKEN_CMD;
	return (lexer->current_token);
}

t_Token	lexer_next_token(t_Lexer *lexer)
{
	char	*input;
	size_t	length;

	input = lexer->input;
	length = 0;
	lexer->current_token.value = malloc(sizeof(char) * ft_strlen(input) + 1);
	if (!lexer->current_token.value)
		exit(1);
	while (input[lexer->pos] != '\0')
	{
		if (isspace(input[lexer->pos]) && lexer->pos++)
			continue ;
		if (!mapchr(&input[lexer->pos]) && input[lexer->pos])
			return (lexer_next_helper0(lexer, input, length));
		if (input[lexer->pos] == '(')
			return (lexer_next_helper1(lexer));
		if (input[lexer->pos] == ')')
			return (lexer_next_helper2(lexer));
		if (mapchr(&input[lexer->pos]))
			return (lexer_next_helper3(lexer, input));
		lexer->pos++;
	}
	lexer->current_token.type = TOKEN_END;
	return (lexer->current_token.value[0] = '\0', lexer->current_token);
}
