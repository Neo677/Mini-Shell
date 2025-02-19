/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 00:34:50 by dpascal           #+#    #+#             */
/*   Updated: 2024/11/12 18:32:52 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n, char *base, int len, int fd)
{
	int	baselen;

	if (n == -2147483648)
	{
		len += ft_putstr("-2147483648", fd);
		return (len);
	}
	if (n < 0)
	{
		ft_putchar('-', fd);
		n = n * -1;
		len++;
	}
	baselen = ft_strlen(base);
	if (n >= baselen)
		len = ft_putnbr(n / baselen, base, len, fd);
	len += ft_putchar(base[n % baselen], fd);
	return (len);
}
/*
int	main(void)
{
	long long	n;

	n = 1234;
	ft_putnbr(n, "0123456789abcdef", 0);
	return (0);
}*/
