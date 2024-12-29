/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-rese <ade-rese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:54:07 by ade-rese          #+#    #+#             */
/*   Updated: 2024/07/25 14:54:07 by ade-rese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler_fork(int sig)
{
	if (sig == SIGINT)
		g_signret = 130;
	if (sig == SIGQUIT)
		g_signret = 131;
}

void	re_set_signal_action(void)
{
	signal(SIGINT, sig_handler_fork);
	signal(SIGQUIT, sig_handler_fork);
}

void	block_signal(int signal)
{
	sigset_t	sigset;

	sigemptyset(&sigset);
	sigaddset(&sigset, signal);
	if (signal == SIGINT)
	{
		g_signret = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigint_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	block_signal(SIGINT);
}

void	set_signal_action(void)
{
	struct sigaction	act;
	struct sigaction	act2;

	ft_bzero(&act, sizeof(act));
	ft_bzero(&act2, sizeof(act2));
	act.sa_handler = &sigint_handler;
	act2.sa_handler = SIG_IGN;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGQUIT, &act2, NULL);
}
