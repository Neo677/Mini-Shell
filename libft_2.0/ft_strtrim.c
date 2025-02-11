/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:31:04 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:31:05 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*dest;

	dest = NULL;
	if (s1)
	{
		while (*s1 && set && ft_strchr(set, (int)*s1))
			s1++;
		i = ft_strlen_v2(s1);
		while (i > 0 && set && ft_strchr(set, (int)s1[i - 1]))
			i--;
		dest = ft_calloc(i + 1, sizeof(char));
		if (dest)
			ft_strlcpy(dest, s1, i + 1);
	}
	return (dest);
}
/*int main(void)
{
	const char s1[] = "  basshab   ";
	char *dst = "basshab";
	ft_putstr_fd(ft_strtrim(s1, dst), 1);
	return (0);
}*/
/*return NULL si s1 = NULL*/