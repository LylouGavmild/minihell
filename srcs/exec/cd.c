/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:01:05 by abutet            #+#    #+#             */
/*   Updated: 2024/12/04 11:20:59 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cd_home(char *home, char ***env, int nbcmd)
{
	char	*pwd;

	if (!home)
		return (write(2, "minishell: cd: HOME not set\n", 28), 1);
	pwd = expand(*env, NULL, "PWD");
	if (access((const char *)home, F_OK))
	{
		if (home[0])
			return (write(2, "minishell: cd: ", 15),
				write(2, home, ft_strlen(home)),
				write(2, ": No such file or directory\n", 28),
				free(pwd), free(home), 1);
		return (0);
	}
	if (nbcmd != 0)
		return (free(pwd), 0);
	if (chdir((const char *)home) != 0)
		return (free(pwd), write(2, "minishell: cd: ", 15),
			write(2, home, ft_strlen(home)),
			write(2, ": Not a directory\n", 18), 1);
	set_pwd(pwd, env, 0);
	set_pwd(getcwd(NULL, 0), env, 1);
	return (free(home), 0);
}

int	cd_dir(char *path, char ***env, char *a, int nbcmd)
{
	char	*pwd;

	(void) env;
	if (!path)
		return (write(2, "minishell: cd: no path var\n", 27), 1);
	pwd = expand(*env, NULL, "PWD");
	if (access((const char *)path, F_OK))
		return (write(2, "minishell: cd: ", 15),
			write(2, a, ft_strlen(a)),
			write(2, ": No such file or directory\n", 28), free(pwd), 1);
	if (nbcmd != 0)
		return (free(pwd), 0);
	if (chdir((const char *)path) != 0)
		return (free(pwd), write(2, "minishell: cd: ", 15),
			write(2, path, ft_strlen(path)),
			write(2, ": Not a directory\n", 18), 1);
	set_pwd(pwd, env, 0);
	set_pwd(getcwd(NULL, 0), env, 1);
	return (0);
}

int	cd_rela(t_temp *commande, char ***env, int nbcmd)
{
	int		i;
	char	*path;
	char	*tmp;

	path = getcwd(NULL, 0);
	if (!path)
		return (write(2, "minishell: cd: ", 15),
			write(2, commande->cmd[1], ft_strlen(commande->cmd[1])),
			write(2, ": No such file or directory\n", 28), 1);
	tmp = ft_strjoin(path, "/");
	free(path);
	path = ft_strjoin(tmp, commande->cmd[1]);
	free(tmp);
	i = cd_dir(path, env, commande->cmd[1], nbcmd);
	free(path);
	return (i);
}

int	my_cd(t_temp *commande, t_Minishell *mini)
{
	int		i;

	i = ft_maplen(commande->cmd);
	if (i == 1)
		return (cd_home(expand(mini->envp[0], NULL, "HOME"), mini->envp,
				mini->nbcmd - 1));
	if (i > 2)
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	if (commande->cmd[1][0] == '/')
		return (cd_dir(commande->cmd[1], mini->envp, commande->cmd[1],
				mini->nbcmd - 1));
	else
		return (cd_rela(commande, mini->envp, mini->nbcmd - 1));
	return (0);
}
