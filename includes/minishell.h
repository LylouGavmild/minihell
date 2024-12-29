/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-rese <ade-rese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:03:44 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/29 15:00:48 by ade-rese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "parsing.h"
# include "btree.h"
# include "exec.h"
# include <dirent.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <termios.h>

extern int	g_signret;

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize);
int		here_doc(char **lim, t_Minishell *mini);

int		writeerror(char	*str);

/***************** signals *********************/
void	set_signal_action(void);
void	block_signal(int signal);
void	sigint_handler(int signal);

/***************** libft_utils *****************/
char	**ft_split2(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		ft_atoi(char *nptr);
int		as_one_white_space(char *str);
int		exit_door(char *line, int exit_code);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, void *src, size_t n);
size_t	ft_strlen(char *str);
size_t	ft_strlcpy(char *dst, char *src, size_t size);

#endif
