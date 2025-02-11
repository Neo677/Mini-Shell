/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:35:40 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 15:35:42 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(long int n)
{
	int	len;

	if (n < 0)
		n *= -1;
	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	itoa_recur(long n, int i, char *rslt)
{
	rslt[i] = n % 10 + '0';
	if (i > 0)
		itoa_recur(n / 10, i - 1, rslt);
}

char	*ft_itoa(int n)
{
	int		len;
	long	l_n;
	char	*rslt;

	len = ft_numlen(n);
	l_n = n;
	if (l_n < 0)
	{
		l_n = l_n * -1;
		len++;
	}
	rslt = malloc(sizeof(char) * (len + 1));
	if (rslt == NULL)
		return (NULL);
	rslt[len] = 0;
	itoa_recur(l_n, len - 1, rslt);
	if (n < 0)
		rslt[0] = '-';
	return (rslt);
}
/*int main(void)
{
	printf("%s\n", ft_itoa(10));
	return (0);
}*/