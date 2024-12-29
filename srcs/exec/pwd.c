/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:41:53 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:19:41 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd(t_temp *commande)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (write(2, "pwd: error retrieving current directory: ge", 43),
			write(2, "tcwd: cannot access parent directories: No such ", 48),
			write(2, "file or directory\n", 18), 1);
	if (write(commande->out, cwd, ft_strlen(cwd)) == -1)
		return (free(cwd), writeerror("pwd"));
	write(commande->out, "\n", 1);
	free(cwd);
	return (0);
}
