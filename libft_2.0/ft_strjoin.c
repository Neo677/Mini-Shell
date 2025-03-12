/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 20:07:59 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/05 20:10:57 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_v2(char const *s1, char const *s2)
{
	int		len;
	int		i;
	char	*str;

	len = 0;
	if (*s1)
		len += ft_strlen_v2(s1);
	if (*s2)
		len += ft_strlen_v2(s2);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		str[i] = *s2++;
		i++;
	}
	str[len] = '\0';
	return (str);
}

// int	main(void)
// {
//     char *s1 = "hello";
//     char *s2 = "World";
//     char *str1 = ft_strjoin(s1, s2);
//     printf("%s\n", str1);
//     char *s3 = NULL;
//     char *s4 = "World";
//     char *str2 = ft_strjoin(s3, s4);
//     printf("the first is NULL %s\n", str2);
//     char *s5 = "hello ";
//     char *s6 = NULL;
//     char *str3 = ft_strjoin(s5, s6);
//     printf("the second is NULL %s\n", str3);
//     char *s7 = NULL;
//     char *s8 = NULL;
//     char *str4 = ft_strjoin(s7, s8);
//     printf("the third is NULL %s\n", str4);
//     return (0);
// }
