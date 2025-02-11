/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 02:58:37 by dpascal           #+#    #+#             */
/*   Updated: 2025/01/19 13:24:44 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_uputnbr(unsigned int n, char *base, int len, int fd)
{
	unsigned int	baselen;

	baselen = ft_strlen_pf(base);
	if (n >= baselen)
		len = ft_uputnbr(n / baselen, base, len, fd);
	len += ft_putchar(base[n % baselen], fd);
	return (len);
}
/*
int	main(void)
{
	unsigned long long	n;

	n = 1234;
	ft_uputnbr(n, "0123456789abcdef", 0);
	return (0);
}*/
