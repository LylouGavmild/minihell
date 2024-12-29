/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:25:06 by abutet            #+#    #+#             */
/*   Updated: 2024/12/04 10:40:18 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BTREE_H
# define BTREE_H

typedef struct s_temp
{
	char	**cmd;
	int		in;
	int		out;
}			t_temp;

typedef struct Minishell
{
	char			***envp;
	t_Node			*origine;
	int				level;
	int				nbcmd;
	int				nbcmdtmp;
	t_temp			*commande;
	int				exit_code;
	int				nbbuiltins;
	char			**noenv;
	struct termios	*origin_term;
}	t_Minishell;

void	re_set_signal_action(void);

int		btree_main(char *input, t_Minishell *mini);
int		btree_if(t_Minishell *mini, t_Node	*nroot, int l);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strjoin_w_free(char *s1, char *s2);

char	**spesplit(char *s, t_Minishell *mini);
void	spesplit4(char *s, char **sn, int *i);
char	**splitw(char *str, char ***sn, int *j, int *start);
void	triewilds(char **str);
void	snjoin(char *s, char ***sn, int *i);
int		splitslash(char *s, char **sn, int *i, int j);
int		splitexpand(char *s, char **sn, int *i, t_Minishell *mini);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
char	*splitjoin(char *s1, char c);

char	*expand(char **env, char **noenv, char *str);
int		is_whitespace(char c);
int		only_white_space(char *str);
size_t	strlenmal(char *s);

int		unset(char **env, char **noenv, t_temp *commande);

int		export(t_temp *commande, t_Minishell *mini);
int		export_env(t_temp *commande, t_Minishell *mini);
int		export_print(t_Minishell *mini, int fd);
void	env_copy(char **env, char **envp);
void	shell_lvl(char **env);
void	env_printer(char **env);
int		my_env(t_temp *commande, char **env);
void	init_env(char **env);

int		maplen(char **str);
char	**malloc_fus(char **map1, char **map2);
char	**mapcp(char **map);

#endif
