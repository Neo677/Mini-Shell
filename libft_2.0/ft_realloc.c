/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:41:24 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/10 22:57:40 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t new)
{
	char	*new_ptr;
	size_t	cursize;

	if (ptr == 0)
		return (malloc(new));
	cursize = sizeof(ptr);
	if (new <= cursize)
		return (ptr);
	new_ptr = malloc(new);
	ft_memcpy(new_ptr, ptr, cursize);
	free(ptr);
	return (new_ptr);
}
