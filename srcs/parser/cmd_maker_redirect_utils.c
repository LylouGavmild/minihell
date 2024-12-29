/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_maker_redirect_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:58:58 by abutet            #+#    #+#             */
/*   Updated: 2024/12/02 15:48:25 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**malloc_fus(char **map1, char **map2)
{
	char	**mapr;
	int		len;
	int		i;

	len = ft_maplen(map1) + ft_maplen(map2);
	mapr = malloc(sizeof(char *) * (len + 3));
	if (!mapr)
		exit(1);
	len = 0;
	while (map1[len])
	{
		mapr[len] = map1[len];
		len++;
	}
	i = 0;
	while (map2[i])
	{
		mapr[len + i] = map2[i];
		i++;
	}
	mapr[len + i] = NULL;
	free (map1);
	return (mapr);
}

char	**mapcp(char **map)
{
	char	**re;
	int		i;

	re = malloc(sizeof(char *) * (maplen(map) + 1));
	if (!re)
		exit(1);
	i = -1;
	while (map[++i])
		re[i] = ft_strdup(map[i]);
	return (re[i] = NULL, re);
}

int	btree_file_helper(t_Minishell *mini, t_Node *root)
{
	char	**re;

	re = spesplit(root->right->token.value, mini);
	if (btree_reif(mini, root, re))
		return (free_map(re), 4);
	if (re[1])
		mini->commande[mini->nbcmd - 1].cmd
			= malloc_fus(mini->commande[mini->nbcmd - 1].cmd, &re[1]);
	return (free(re[0]), free(re), 0);
}
