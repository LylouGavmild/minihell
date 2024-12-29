/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 10:48:08 by ade-rese          #+#    #+#             */
/*   Updated: 2024/11/19 10:35:03 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_close(t_struct *stru)
{
	free_struct(stru);
	if (stru->in > 0)
		close(stru->in);
	if (stru->out > 1)
		close(stru->out);
	exit(1);
}

void	init_struct(t_struct *stru)
{
	stru->arg_spl = NULL;
	stru->spl_path = NULL;
	stru->joined = NULL;
	stru->ch = NULL;
	stru->prev = 0;
}

void	free_struct(t_struct *stru)
{
	int	i;

	i = -1;
	if (stru->ch)
		free(stru->ch);
	if (stru->arg_spl)
	{
		while (stru->arg_spl[++i])
		{
			if (stru->arg_spl[i] == stru->joined)
				stru->joined = NULL;
			free(stru->arg_spl[i]);
		}
		free(stru->arg_spl);
		stru->arg_spl = NULL;
		i = -1;
	}
	if (stru->spl_path)
		while (stru->spl_path[++i])
			free(stru->spl_path[i]);
	free(stru->spl_path);
	if (stru->joined)
		free(stru->joined);
}

void	exit_fork(t_struct *stru, t_Minishell *mini, char *msg, int num)
{
	if (msg)
	{
		free_struct(stru);
		write(2, msg, ft_strlen(msg));
	}
	else
		free(stru->ch);
	clear_history();
	free_cmd(mini->nbcmd - 1, mini->commande);
	free_map(*(mini->envp));
	free(mini->envp);
	free_map(mini->noenv);
	exit(num);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*sj;
	int		n;
	int		n1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	n = ft_strlen(s1);
	n1 = ft_strlen(s2);
	sj = (char *)malloc((sizeof(char) * n) + (sizeof(char) * n1) + 1);
	if (!sj)
		return (NULL);
	while (s1[i] != '\0')
		sj[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		sj[j++] = s2[i++];
	sj[j] = '\0';
	return (sj);
}
