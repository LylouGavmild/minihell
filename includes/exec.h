/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 12:29:47 by ade-rese          #+#    #+#             */
/*   Updated: 2024/12/02 15:49:51 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_struct
{
	int		i;
	int		pipe;
	int		in;
	int		out;
	int		prev;
	int		here_doc;
	pid_t	*ch;
	char	*joined;
	char	**arg_spl;
	char	**spl_path;
}			t_struct;

char	*ft_itoa(int n);

char	*securedirect(t_Minishell *mini, char *str);
char	*btreeexpand(char *str, t_Minishell *mini);
int		btreeexpand3(char *str, char **re, int *len, t_Minishell *mini);
char	*btreeexpand6(char *str, char *s, int *len, t_Minishell *mini);
int		btreeexpand5(char *str, char **re, int *len, t_Minishell *mini);

char	**dirreader(char *cwd);
int		patern_finder(char *str, char *patern);
char	**malloc_resize(char **map1, char **map2, char *str);

int		btree_dpipe(t_Minishell *mini, t_Node *root, int l);
int		btree_and(t_Minishell *mini, t_Node *root, int l);
int		btree_spipe(t_Minishell *mini, t_Node *root, int l);
int		btree_cmd(t_Minishell *mini, t_Node *root);
int		btree_file_helper(t_Minishell *mini, t_Node *root);
int		btree_redirect(t_Minishell *mini, t_Node *root, int l, int r);
int		btree_reif(t_Minishell *mini, t_Node *root, char **redirect);

int		cmd(t_Minishell *mini);
int		wpids(t_struct *stru, int i, t_Minishell *mini);
void	free_map(char **map);
void	free_cmd(int nbcmd, t_temp *commande);
size_t	ft_maplen(char **map);

void	fd_distri(t_temp *commande, int nbcmd);
void	close_all(t_temp *commande, int nbcmd);

int		build(t_struct *stru, t_Minishell *mini, int i);
int		is_build(t_Minishell *mini, int i);
int		ft_exit(t_temp *commande, int pipe, int j, t_Minishell *mini);
int		exit_exit(int err, int i, t_temp *commande, t_Minishell *mini);
int		ft_echo(t_temp *commande);
int		my_cd(t_temp *commande, t_Minishell *mini);
char	**set_pwd(char *pwd, char ***env, int b);
int		pwd(t_temp *commande);

int		ft_atocoi(char *str);
int		ft_is_numeric(char *str);
void	exit_close(t_struct *stru);
void	init_struct(t_struct *stru);
void	free_struct(t_struct *stru);
void	exit_fork(t_struct *stru, t_Minishell *mini, char *msg, int num);
void	childminder(t_struct *stru, t_temp *commande,
			t_Minishell *mini, int i);
void	child_one(t_struct *stru, t_Minishell *mini, int i);
char	*get_next_line(int fd);
char	**ft_split2(char *s);
char	**ft_split(char *s, char c);
char	*command_check(t_struct *stru, t_temp *commande,
			t_Minishell *mini, int l);
char	*ft_substr(char *s, unsigned int start, size_t len);
int		check_if_dir(t_struct *stru, t_temp *commande,
			t_Minishell *mini, int l);
void	prexit(t_struct *stru, t_Minishell *mini, int l, int i);
char	*pathset(t_Minishell *mini, t_struct *stru, int l, int err);
int		exit_fperror(t_struct *stru, t_temp *commande,
			t_Minishell *mini, int num);
size_t	ft_strlen(char *str);
char	*ft_strdup(char *s1);

#endif
