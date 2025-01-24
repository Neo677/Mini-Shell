/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_adress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 01:16:41 by dpascal           #+#    #+#             */
/*   Updated: 2025/01/15 11:52:10 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_p_adress(unsigned long p, int len, int fd)
{
	if (!p)
	{
		len += ft_putstr("(nil)", fd);
		return (len);
	}
	len += ft_putstr("0x", fd);
	len = ft_putnbr_adr(p, "0123456789abcdef", len, fd);
	return (len);
}
