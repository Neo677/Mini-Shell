/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_adr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 23:31:52 by dpascal           #+#    #+#             */
/*   Updated: 2025/01/19 13:24:31 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_adr(unsigned long n, char *base, int len, int fd)
{
	unsigned long	baselen;

	baselen = ft_strlen_pf(base);
	if (n >= baselen)
		len = ft_putnbr_adr(n / baselen, base, len, fd);
	len += ft_putchar(base[n % baselen], fd);
	return (len);
}
