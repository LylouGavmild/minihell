/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 12:19:59 by abutet            #+#    #+#             */
/*   Updated: 2024/10/23 12:31:49 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mapchr(char *c)
{
	if (!c || *c == '\0')
		return (0);
	if (!ft_strncmp("&&", c, 2) || !ft_strncmp("||", c, 2)
		|| !ft_strncmp("<<", c, 2) || !ft_strncmp(">>", c, 2))
		return (2);
	if (!ft_strncmp("|", c, 1) || !ft_strncmp("<", c, 1)
		|| !ft_strncmp(">", c, 1) || !ft_strncmp("(", c, 1)
		|| !ft_strncmp(")", c, 1))
		return (1);
	return (0);
}

void	lexer_init(t_Lexer *lexer, char *input)
{
	lexer->input = input;
	lexer->pos = 0;
	lexer->current_token.type = TOKEN_END;
}
