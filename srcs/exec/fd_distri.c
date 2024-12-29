/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_distri.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 08:28:29 by abutet            #+#    #+#             */
/*   Updated: 2024/11/26 16:13:54 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fd_in(t_temp *commande, int i, int prev)
{
	if (i == 0)
	{
		if (!commande[i].in)
			commande[i].in = 0;
	}
	else
	{
		if (!commande[i].in)
			commande[i].in = prev;
		else
		{
			if (prev > 1)
				close(prev);
		}
	}
}

void	fd_out(t_temp *commande, int pip[], int i, int nbcmd)
{
	if (i == nbcmd - 1)
	{
		if (!commande[i].out)
			commande[i].out = 1;
		if (pip[1] > 1)
			close(pip[1]);
	}
	else
	{
		if (!commande[i].out)
		{
			commande[i].out = pip[1];
		}
		else
		{
			if (pip[1] > 1)
				close(pip[1]);
		}
	}
}

void	fd_distri(t_temp *commande, int nbcmd)
{
	int	i;
	int	pip[2];
	int	prev;

	i = -1;
	prev = 0;
	if (!nbcmd)
		return ;
	while (++i < nbcmd)
	{
		pipe(pip);
		fd_in(commande, i, prev);
		fd_out(commande, pip, i, nbcmd);
		prev = pip[0];
	}
	if (prev > 1)
		close(prev);
}
