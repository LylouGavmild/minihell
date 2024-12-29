/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-rese <ade-rese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:47:21 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/29 15:29:41 by ade-rese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_heredoc(int b, char **lim, int *fd_write)
{
	static char		**static_lim = NULL;
	static int		*static_fd_write = NULL;

	if (b)
	{
		static_lim = lim;
		static_fd_write = fd_write;
	}
	if (!b)
	{
		free(*static_lim);
		close(*static_fd_write);
	}
}

void	sig_handler_heredoc(int signum)
{
	(void)signum;
	g_signret = 130;
	write(1, "\n", 1);
	rl_redisplay();
	exit_heredoc(0, NULL, NULL);
	exit(130);
}

void	here_doc_helper(int *fd, char **line, char *lim)
{
	write(fd[1], *line, ft_strlen(*line));
	write(fd[1], "\n", 1);
	free(*line);
	*line = readline("heredoc>");
	if (!*line)
	{
		close(fd[1]);
		write(2, "minishell: warning: last here-document ", 39);
		write(2, "line delimited by end-of-file (wanted `", 39);
		write(2, lim, ft_strlen(lim));
		write(2, "')\n", 3);
		free(lim);
		exit(1);
	}
}

int	here_doc_child(char *lim, int *fd)
{
	char	*line;

	exit_heredoc(1, &lim, &fd[1]);
	signal(SIGINT, &sig_handler_heredoc);
	line = readline("heredoc>");
	if (!line)
	{
		close(fd[1]);
		write(2, "minishell: warning: last here-document ", 39);
		write(2, "line delimited by end-of-file (wanted `", 39);
		write(2, lim, ft_strlen(lim));
		write(2, "')\n", 3);
		free(lim);
		exit(1);
	}
	while (ft_strncmp(line, lim, ft_strlen(lim))
		|| !((ft_strlen(lim)) == ft_strlen(line)))
		here_doc_helper(fd, &line, lim);
	free(line);
	close(fd[1]);
	free(lim);
	exit(0);
}

int	here_doc(char **lim, t_Minishell *mini)
{
	int		fd[2];
	int		forkid[2];
	int		i;
	char	*re;

	(pipe(fd), signal(SIGINT, SIG_IGN));
	if (fd[0] < 0 || fd[1] < 0)
		return (printf("pipe error\n"), -1);
	forkid[0] = fork();
	if (!forkid[0])
	{
		re = *lim;
		i = 0;
		while (lim[++i])
			free(lim[i]);
		return (free(lim), free_btree(mini->origine), close(fd[0]),
			clear_history(), free_cmd(mini->nbcmd - 1, mini->commande),
			free_map(*(mini->envp)), free(mini->envp),
			free_map(mini->noenv), here_doc_child(re, fd));
	}
	waitpid(forkid[0], &forkid[1], 0);
	tcsetattr(STDIN_FILENO, TCSANOW, mini->origin_term);
	if (WIFEXITED(forkid[1]) && WEXITSTATUS(forkid[1]) == 130)
		return (close (fd[0]), close (fd[1]), -130);
	return (close (fd[1]), fd[0]);
}
