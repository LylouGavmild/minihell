/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wpids.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-rese <ade-rese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:35:38 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 15:11:55 by ade-rese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	writepid(int err, int *quit, int *b)
{
	if (quit[0] && WEXITSTATUS(err))
		b[0]++;
	if (!quit[0] && WIFSIGNALED(err) && g_signret == 131)
		(write(2, "Quit (core dumped)\n", 19), quit[0] = 1);
	if (!quit[0] && WIFSIGNALED(err) && g_signret == 130)
		(write(2, "\n", 1), quit[0] = 1);
}

int	wpids(t_struct *stru, int i, t_Minishell *mini)
{
	int	pid;
	int	err;
	int	quit;
	int	b;

	pid = 0;
	err = 0;
	b = 0;
	quit = 0;
	re_set_signal_action();
	while (pid < stru->i - i)
	{
		if (stru->ch[pid] != -1)
		{
			waitpid(stru->ch[pid], &err, 0);
			tcsetattr(STDIN_FILENO, TCSANOW, mini->origin_term);
			writepid(err, &quit, &b);
		}
		pid++;
	}
	if (!b && quit)
		return (err = g_signret, g_signret = 0, err);
	if (WEXITSTATUS(err))
		return (WEXITSTATUS(err));
	return (0);
}
