/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:44:02 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:44:22 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen_v2(s) + 1));
}

// int main()
// {
// 	const char *s = "Hello my world !";
// 	int	c = '1';
// 	char first_occurence = ft_strchr(s, c);

// 	if (first_occurence != NULL)
// 		printf("premier occurence de %c est trouve a index $ld\n",
//			first_occurence, c);
// 	else
// 		printf("Le carac %c n'est pas dans la chaine :(\n", c);
// 	return (0);
// }
