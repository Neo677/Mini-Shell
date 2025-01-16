/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 00:04:55 by dpascal           #+#    #+#             */
/*   Updated: 2025/01/15 11:52:30 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_written(const char *format, va_list args, int len, t_data *data)
{
	if (format[data->i] == 'c')
		len += ft_putchar(va_arg(args, int), data->fd);
	else if (format[data->i] == 's')
		len += ft_putstr(va_arg(args, char *), data->fd);
	else if (format[data->i] == 'p')
		len = ft_p_adress(va_arg(args, unsigned long), len, data->fd);
	else if (format[data->i] == 'd' || format[data->i] == 'i')
		len = ft_putnbr(va_arg(args, int), "0123456789", len, data->fd);
	else if (format[data->i] == 'u')
		len = ft_uputnbr(va_arg(args, unsigned int), "0123456789", len,
				data->fd);
	else if (format[data->i] == 'x')
		len = ft_uputnbr(va_arg(args, unsigned int), "0123456789abcdef", len,
				data->fd);
	else if (format[data->i] == 'X')
		len = ft_uputnbr(va_arg(args, unsigned int), "0123456789ABCDEF", len,
				data->fd);
	else if (format[data->i] == '%')
		len += ft_putchar('%', data->fd);
	return (len);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	int		len;
	va_list	args;
	t_data	data;

	data.fd = fd;
	data.i = 0;
	len = 0;
	va_start(args, format);
	while (format[data.i])
	{
		if (format[data.i] == '%')
		{
			data.i++;
			len = ft_written(format, args, len, &data);
		}
		else
		{
			ft_putchar(format[data.i], data.fd);
			len++;
		}
		data.i++;
	}
	va_end(args);
	return (len);
}
