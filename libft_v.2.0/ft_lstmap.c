/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:36:01 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/05 19:22:58 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tm;

	if (!lst || !f)
		return (NULL);
	new = NULL;
	while (lst)
	{
		tm = ft_lstnew(f(lst->content));
		if (!tm)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, tm);
		lst = lst->next;
	}
	return (new);
}
/*applique la fonction a chaque element
et cree un new pour le rslt
nettoie la new lst 
add les elements a la fin de la liste
passe au suivant
lst_map applique une F a chaque element de la liste, 
creant une new lst avec le resultat ;)*/
