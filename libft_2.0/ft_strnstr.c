/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:31:23 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:31:28 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	if (to_find[0] == '\0')
		return ((char *)s);
	i = 0;
	while (s[i] && i < n)
	{
		if (s[i] == to_find[0] && ft_strlen_v2(to_find) <= n - i)
		{
			j = 0;
			while (s[i + j] && to_find[j] && s[i + j] == to_find[j])
			{
				j++;
			}
			if (to_find[j] == '\0')
				return ((char *)s + (i));
		}
		i++;
	}
	return (NULL);
}

//  int     main(int ac, char **av)
// {
// 	if (ac == 3)
//     {
//         printf("%s\n", ft_strnstr(av[1], av[2], ft_strlen(av[1])));
//         printf("%s\n", strnstr(av[1], av[2], ft_strlen(av[1])));
//     }
//     return (0);
// }
