/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-rese <ade-rese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:03:27 by ade-rese          #+#    #+#             */
/*   Updated: 2024/12/05 09:40:41 by ade-rese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_signret = 0;

int	env_import(char **envp, t_Minishell *mini)
{
	mini->envp = NULL;
	mini->noenv = NULL;
	mini->envp = malloc(sizeof(char ***));
	if (!mini->envp)
		return (1);
	if (!envp[0])
	{
		*(mini->envp) = NULL;
		*(mini->envp) = malloc(sizeof(char *) * 5);
		if (!*(mini->envp))
			return (1);
		init_env(*(mini->envp));
	}
	else
	{
		*(mini->envp) = NULL;
		*(mini->envp) = malloc(sizeof(char *) * (maplen(envp) + 1));
		if (!*(mini->envp))
			return (1);
		env_copy(*(mini->envp), envp);
		shell_lvl(mini->envp[0]);
	}
	return (0);
}

int	noenvset(t_Minishell *mini)
{
	mini->noenv = NULL;
	mini->noenv = malloc(sizeof(char **) * 4);
	if (!mini->noenv)
		return (1);
	mini->noenv[0] = ft_strdup(
			"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
			);
	if (!mini->noenv[0])
		return (write(2, "NOP\n", 4), 1);
	mini->noenv[1] = ft_strdup("TERM=dumb");
	if (!mini->noenv[1])
		return (write(2, "NOP\n", 4), 1);
	mini->noenv[2] = ft_strdup("SHELL=/bin/zsh");
	if (!mini->noenv[2])
		return (write(2, "NOP\n", 4), 1);
	mini->noenv[3] = NULL;
	return (0);
}

int	only_white_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_whitespace(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	micro_main(t_Minishell *mini)
{
	char		*line;

	line = readline("minishell-1.2$ ");
	while (line)
	{
		if (g_signret == 130)
		{
			mini->exit_code = 130;
			g_signret = 0;
		}
		if (only_white_space(line))
		{
			add_history(line);
			if (!line[0])
			{
				free(line);
				line = readline("minishell-1.2$ ");
				continue ;
			}
			mini->exit_code = btree_main(line, mini);
		}
		line = readline("minishell-1.2$ ");
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_Minishell		mini;
	struct termios	tmp;

	mini.origin_term = &tmp;
	tcgetattr(STDIN_FILENO, mini.origin_term);
	(void) argv;
	mini.exit_code = 0;
	if (argc != 1)
		return (write(2, "Error: trying to add arguments\n", 31), 1);
	set_signal_action();
	if (env_import(envp, &mini))
		exit_exit(1, 0, NULL, &mini);
	if (noenvset(&mini))
		exit_exit(1, 0, NULL, &mini);
	micro_main(&mini);
	write(1, "exit\n", 6);
	exit_exit(0, 0, NULL, &mini);
}
