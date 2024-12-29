/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 07:46:03 by abutet            #+#    #+#             */
/*   Updated: 2024/11/27 10:03:40 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo_option(t_temp *commande, int *i)
{
	size_t	j;
	int		n;

	*i = 1;
	n = 0;
	j = 0;
	while (commande->cmd[*i])
	{
		j = 1;
		if (commande->cmd[*i][0] != '-')
			break ;
		while (commande->cmd[*i][j] == 'n')
			j++;
		if (j != ft_strlen(commande->cmd[*i]))
			break ;
		n = 1;
		*i += 1;
	}
	return (n);
}

int	writeerror(char	*str)
{
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, ": write error: No space left on device\n", 39);
	return (1);
}

int	ft_echo(t_temp *commande)
{
	int	i;
	int	j;
	int	n;

	n = ft_echo_option(commande, &i);
	j = 0;
	while (commande->cmd[i])
	{
		if (j)
			write(commande->out, " ", 1);
		if (write(commande->out, commande->cmd[i],
				ft_strlen(commande->cmd[i])) == -1)
			return (writeerror("echo"));
		j++;
		i++;
	}
	if (!n)
		write(commande->out, "\n", 1);
	return (0);
}
