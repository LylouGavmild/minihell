/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:27:24 by abutet            #+#    #+#             */
/*   Updated: 2024/10/24 10:45:16 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_estim(long n)
{
	size_t	estim;
	int		isneg;

	estim = 0;
	isneg = 0;
	if (n < 0)
	{
		estim++;
		isneg++;
		n = -n;
	}
	while (n >= 1)
	{
		estim++;
		n /= 10;
	}
	return (estim);
}

static char	*ft_gen(char *r, long nbr, int len, int isneg)
{
	if (nbr != 0)
		r = malloc(sizeof(char) * (len + 1));
	else
		return (r = ft_strdup("0"));
	if (!r)
		return (0);
	isneg = 0;
	if (nbr < 0)
	{
		isneg++;
		nbr = -nbr;
	}
	r[len] = '\0';
	while (--len)
	{
		r[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (isneg == 1)
		r[0] = '-';
	else
		r[0] = (nbr % 10) + '0';
	return (r);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*r;
	long	nbr;
	int		isneg;

	nbr = n;
	len = ft_estim(nbr);
	r = 0;
	isneg = 0;
	r = ft_gen(r, nbr, len, isneg);
	if (!r)
		return (0);
	return (r);
}
