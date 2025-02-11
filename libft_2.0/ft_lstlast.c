/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:26:57 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/03 19:47:56 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;

	i = 0;
	while (lst && lst->next)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
/*parcour lst jusque au dernier avance dans la liste
renvoie le dernier element de lst et le return*/