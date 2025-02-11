/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:32:42 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:47:12 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen_v2(src));
	while (dst[i] != '\0' && i < dstsize)
		i++;
	j = i;
	while (src[i - j] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i - j];
		i++;
	}
	if (j < dstsize)
		dst[i] = '\0';
	return (j + ft_strlen_v2(src));
}

// #include <string.h>

// int main(void)
// {
// 	char	dst[] = "je suis la phrase";
// 	char	src[] = "oui cest moi";

// 	printf("strlcat returned : %ld\n", ft_strlcat(dst, src, 40));
//     printf("dst : %s\n", dst);
// }
