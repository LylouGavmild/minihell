/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:07:02 by abutet            #+#    #+#             */
/*   Updated: 2024/12/02 15:43:12 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	scan_env(char **env, char *str, int len)
{
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=' && j < len)
		{
			if (env[i][j] != str[j])
				break ;
			j++;
		}
		if ((!env[i][j] && (!str[j] || str[j] == '='))
			|| (env[i][j] == '=' && (!str[j] || str[j] == '=')))
			return (i);
		i++;
	}
	return (-1);
}

size_t	len_export(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	export_help(t_temp *commande, t_Minishell *mini, char **mal, int i[3])
{
	int	m;

	i[0] = scan_env(mini->envp[0], commande->cmd[i[1]],
			len_export(commande->cmd[i[1]]));
	m = scan_env(mal, commande->cmd[i[1]],
			len_export(commande->cmd[i[1]]));
	if (i[0] == -1 && m == -1)
	{
		mal[i[2]++] = ft_strdup(commande->cmd[i[1]]);
		mal[i[2]] = NULL;
	}
	else if (m == -1)
	{
		if (commande->cmd[i[1]][len_export(commande->cmd[i[1]])] == '=')
			(free(mini->envp[0][i[0]]),
				mini->envp[0][i[0]] = ft_strdup(commande->cmd[i[1]]));
	}
	else
	{
		if (commande->cmd[i[1]][len_export(commande->cmd[i[1]])] == '=')
			(free(mal[m]), mal[m] = ft_strdup(commande->cmd[i[1]]));
	}
}

int	is_exportable(t_temp *commande, int i)
{
	int	j;

	if (ft_isalpha(commande->cmd[i][0]) || commande->cmd[i][0] == '_')
	{
		j = 1;
		while ((ft_isalnum(commande->cmd[i][j]) || commande->cmd[i][j] == '_')
			&& (commande->cmd[i][j] || commande->cmd[i][j] != '='))
			j++;
		if (!commande->cmd[i][j] || commande->cmd[i][j] == '=')
			return (1);
	}
	return (0);
}

int	export_env(t_temp *commande, t_Minishell *mini)
{
	char	**mal;
	int		i[3];
	int		b;

	i[1] = 1;
	i[2] = 0;
	b = 0;
	mal = malloc(sizeof(char *) * maplen(commande->cmd));
	mal[0] = NULL;
	if (!mal)
		exit(1);
	while (commande->cmd[i[1]])
	{
		if (is_exportable(commande, i[1]))
			export_help(commande, mini, mal, i);
		else
		{
			b = 1;
			write(2, "minishell: export: `", 20);
			write(2, commande->cmd[i[1]], ft_strlen(commande->cmd[i[1]]));
			write(2, "': not a valid identifier\n", 26);
		}
		i[1]++;
	}
	return (mini->envp[0] = malloc_fus(mini->envp[0], mal), free(mal), b);
}
