/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutet <abutet@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:58:37 by abutet            #+#    #+#             */
/*   Updated: 2024/11/29 10:19:19 by abutet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_realloc(void *ptr, size_t oldsize, size_t newsize)
{
	void	*new_ptr;

	if (ptr == NULL)
	{
		new_ptr = malloc(newsize);
		if (!new_ptr)
			exit(1);
		return (new_ptr);
	}
	if (!newsize)
		return (ptr);
	new_ptr = malloc(newsize);
	if (!new_ptr)
		exit(1);
	ft_memcpy(new_ptr, ptr, oldsize);
	free(ptr);
	return (new_ptr);
}
