/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 14:58:45 by abutet            #+#    #+#             */
/*   Updated: 2024/11/27 10:15:28 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_fill(char **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	env[0] = ft_strjoin("PWD=", cwd);
	env[1] = ft_strdup("SHLVL=1");
	env[2] = ft_strjoin("_=", cwd);
	env[2] = ft_strjoin_w_free(env[2], "/./minishell");
	env[3] = ft_strdup("OLDPWD");
	free(cwd);
}

void	init_env(char **env)
{
	env[0] = NULL;
	env[1] = NULL;
	env[2] = NULL;
	env[3] = NULL;
	env[4] = NULL;
	env_fill(env);
}

void	env_printer(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

int	whereisequal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	my_env(t_temp *commande, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (whereisequal(env[i]))
		{
			if (write(commande->out, env[i], ft_strlen(env[i])) == -1)
				return (writeerror("env"));
			write(commande->out, "\n", 1);
		}
	}
	return (0);
}
