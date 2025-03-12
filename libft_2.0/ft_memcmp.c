/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:34:45 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:34:50 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n && ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i]))
		i++;
	if (i == n)
		return (0);
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

// int	main(void)
// {
// 	char    *s1;
//     char    *s2;
//     size_t    n;

//     s1 = (char *)malloc(sizeof(char) * 10);
//     s2 = (char *)malloc(sizeof(char) * 10);
//     n = 10;
//     s1[0] = 'a';
//     s1[1] = 'b';
//     s1[2] = 'c';
//     s1[3] = 'd';
//     s1[4] = 'e';
//     s1[5] = 'f';
//     s1[6] = 'g';
//     s1[7] = 'h';
//     s1[8] = 'i';
//     s1[9] = 'j';
//     s2[0] = 'a';
// 	printf("%s\n", s1);
// 	printf("%s\n", s2);
// 	printf("%d\n", ft_memcmp(s1, s2, n));
// }
