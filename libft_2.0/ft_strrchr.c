/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 10:12:29 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/03 14:17:19 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*d;

	i = 0;
	d = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			d = ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (d);
}

/*int main(void)
{
	char	*test = "a b a a a b a";
	char	*dest = ft_strrchr(test, 'b');
	char	*dest1 = strrchr(test, 'b');
	printf ("vrai strrchr %s\n", dest);
	printf ("man strrchr %s\n", dest1);
	return (0);
}*/
