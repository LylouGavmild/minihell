/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:07:02 by abutet            #+#    #+#             */
/*   Updated: 2024/11/27 10:20:25 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export(t_temp *commande, t_Minishell *mini)
{
	if (mini->nbcmd - 1 != 0 && commande->cmd[1])
		return (1);
	if (commande->cmd[1])
		return (export_env(commande, mini));
	else
		return (export_print(mini, commande->out));
	return (0);
}
