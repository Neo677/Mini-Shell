/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:31:53 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:31:54 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned int)s1[i] > (unsigned int)s2[i])
			return (1);
		else if ((unsigned int)s1[i] < (unsigned int)s2[i])
			return (-1);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char *s1 = "Hello";
// 	const char *s2 = "Hello World !";
// 	size_t n = 5;
// 	int rst = ft_strncmp(s1, s2, n);

// 	if (rst < 0)
// 		printf ("%s est inferieur a %s\n", s1, s2);
// 	else if (rst > 0)
// 		printf ("%s est superieur a %s\n", s1, s2);
// 	else
// 		printf ("%s est egal a %s\n", s1, s2);
// 	return (0);
// }
// #define TESTED_STRING1 "abcde"
// #define TESTED_STRING2 "abcd"
// #define TESTED_STRING3 "abcde"
// #define TESTED_STRING4 "abcd"
// #define TESTED_SIZE 5

// void	test_cmp(const void *s1, const void *s2, size_t n)
// {
// 	int		cmp_return (= strncmp(s1, s2, n));

// 	if (cmp_return > 0)
// 		printf("man strncmp(\"%s\", \"%s\", %zu) returned a positive value\n",
//			(char *)s1, (char *)s2, n);
// 	else if (cmp_return < 0)
// 		printf("man strncmp(\"%s\", \"%s\", %zu) returned a negative value\n",
//			(char *)s1, (char *)s2, n);
// 	else
// 		printf("man strncmp(\"%s\", \"%s\", %zu) returned zero\n", (char *)s1,
//			(char *)s2, n);
// }

// void	test_my_cmp(const void *s1, const void *s2, size_t n)
// {
// 	int		cmp_return (= ft_strncmp(s1, s2, n));

// 	if (cmp_return > 0)
// 		printf("my_strncmp(\"%s\", \"%s\", %zu) returned a positive value\n",
//			(char *)s1, (char *)s2, n);
// 	else if (cmp_return < 0)
// 		printf("my_strncmp(\"%s\", \"%s\", %zu) returned a negative value\n",
//			(char *)s1, (char *)s2, n);
// 	else
// 		printf("my_strncmp(\"%s\", \"%s\", %zu) returned zero\n", (char *)s1,
//			(char *)s2, n);
// }

// int main(void)
// {
// 	for (int i = 0; i <= 5; i++)
// 		test_cmp(TESTED_STRING1, TESTED_STRING2, i);
//     for (int i = 0; i <= 5; i++)
// 		test_my_cmp(TESTED_STRING3, TESTED_STRING4, i);
// }