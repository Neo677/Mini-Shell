/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:16:45 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 16:33:50 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tm;

	if (lst && del)
	{
		while (*lst)
		{
			tm = (*lst)-> next;
			ft_lstdelone(*lst, del);
			*lst = tm;
		}
	}
}
/*ptr temporaire pour stocker lelement suivant
prochain element de lst dans tm
 fonction del de suppression
update le ptr de lst pour pointer vers le prochain*/
