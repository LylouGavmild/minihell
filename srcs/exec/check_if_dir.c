/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_dir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:26:30 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/29 09:45:35 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_if_dir(t_struct *stru, t_temp *commande, t_Minishell *mini, int l)
{
	int	i;

	if (!commande[l].cmd[0][0])
		exit_fperror(stru, commande, mini, 127);
	if (!ft_strncmp(commande[l].cmd[0], ".", 2))
		exit_fperror(stru, commande, mini, 2);
	i = open(commande[l].cmd[0], __O_DIRECTORY);
	if (i > 1 && (commande[l].cmd[0][0] == '.' || commande[l].cmd[0][0] == '/'))
	{
		close(i);
		exit_fperror(stru, commande, mini, 126);
	}
	else if (i >= 0)
		close(i);
	return (0);
}
