/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:30:43 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:30:45 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	len_s;

	ptr = NULL;
	if (!s)
		return (NULL);
	len_s = ft_strlen_v2(s);
	if (start >= len_s)
		return (ft_strdup_v2(""));
	if (start + len > len_s)
		len = len_s - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s + start, len + 1);
	return (ptr);
}
/*int     main(void)
{
	char *str;

	str = ft_substr("Hello", 1, 5);
	printf("%s\n", str);
	free(str);
	return (0);
}*/