/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 20:32:07 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/03 20:55:48 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*dernier;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	dernier = ft_lstlast(*lst);
	dernier->next = new;
}
/* ptr pour stocker le dernier element d'une liste
 verifier si la liste est vide
 si oui elle est vide assigne le dernier element a la liste
 obtient le derniere element de la liste
 ajoute new a la fin de la liste en modifiant le ptr next du last element*/