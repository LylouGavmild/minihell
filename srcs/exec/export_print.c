/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:07:02 by abutet            #+#    #+#             */
/*   Updated: 2024/11/27 10:19:12 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

int	export_write(char **env, int fd)
{
	int		i[4];

	i[1] = -1;
	while (++i[1] < maplen(env))
	{
		i[2] = 0;
		i[0] = -1;
		i[3] = 0;
		if (env[i[1]][0] == '_' && (!env[i[1]][0] || env[i[1]][1] == '='))
			continue ;
		if (write(fd, "export ", 7) == -1)
			return (writeerror("export"));
		while (env[i[1]][++i[0]])
		{
			if (env[i[1]][i[0]] == '"')
				write(fd, "\\", 1);
			write(fd, &env[i[1]][i[0]], 1);
			if (env[i[1]][i[0]] == '=' && !i[3]++ && ++i[2])
				write(fd, "\"", 1);
		}
		if (i[2])
			write(fd, "\"", 1);
		write(fd, "\n", 1);
	}
	return (0);
}

int	export_print(t_Minishell *mini, int fd)
{
	int		i[3];
	char	**env;
	int		r;

	env = malloc(sizeof(char *) * (maplen(mini->envp[0]) + 1));
	env_copy(env, mini->envp[0]);
	i[0] = 0;
	while (i[0] < maplen(env))
	{
		i[1] = 0;
		while (i[1] < maplen(env) - 1)
		{
			if (ft_strncmp(env[i[1]], env[i[1] + 1],
					ft_strlen(env[i[1]])) > 0)
				ft_swap(&env[i[1]], &env[i[1] + 1]);
			i[1]++;
		}
		i[0]++;
	}
	r = export_write(env, fd);
	free_map(env);
	return (r);
}
