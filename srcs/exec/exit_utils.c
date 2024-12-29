/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:28:27 by abutet            #+#    #+#             */
/*   Updated: 2024/10/11 10:28:44 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static char	*skip_whitespace(char *str)
{
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	return (str);
}

int	ft_atocoi(char *str)
{
	long	sign;
	long	number;

	sign = 1;
	str = skip_whitespace(str);
	number = 0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_is_numeric(str))
	{
		if (number > (LONG_MAX - (*str - '0')) / 10)
			if (sign == 1 || (sign == -1
					&& number > (LONG_MAX - (*str - '0') + 1) / 10))
				return (1);
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (0);
}
