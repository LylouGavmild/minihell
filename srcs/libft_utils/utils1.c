/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-rese <ade-rese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:32:27 by ade-rese          #+#    #+#             */
/*   Updated: 2024/07/23 14:32:27 by ade-rese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_atoi(char *nptr)
{
	unsigned int	nb;
	unsigned int	i;
	int				sign;

	nb = 0;
	i = 0;
	sign = 1;
	while ((nptr[i] != '\0') && (nptr[i] == ' ' || (nptr[i] >= 9
				&& nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-')
		sign = -1;
	if (nptr[i] == '-' || nptr[i] == '+')
		i++;
	while ((nptr[i] != '\0') && nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		i++;
	}
	return (nb * sign);
}

int	exit_door(char *line, int exit_code)
{
	char	**exit_line;
	int		i;

	i = 0;
	exit_line = ft_split2(line);
	if (!exit_line)
		return (write(2, "Error: happend while spliting for exit\n", 39), 1);
	if (exit_line[1])
		exit_code = ft_atoi(exit_line[1]);
	if (exit_line)
	{
		while (exit_line[i])
			free(exit_line[i++]);
		free(exit_line);
	}
	return ((unsigned char)exit_code);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	i = 0;
	while (n > 0)
	{
		((char *)s)[i] = '\0';
		i++;
		n--;
	}
}
