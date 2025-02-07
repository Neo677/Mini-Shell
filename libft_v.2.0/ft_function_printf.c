/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_function_printf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:47:24 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/16 10:47:28 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlent(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar_fd_two(char s, int fd, int *count)
{
	*count += write(fd, &s, 1);
}

void	ft_putstr_fd_two(char *s, int fd, int *count)
{
	if (!s)
	{
		ft_putstr_fd_two("(null)", 1, count);
		return ;
	}
	while (*s)
		ft_putchar_fd_two(*s++, fd, count);
}

void	ft_putnbr_basefd_one(long long n, char *base, int fd, int *count)
{
	long long	len_base;

	if (n < 0)
	{
		ft_putchar_fd_two('-', fd, count);
		n = n * -1;
	}
	len_base = ft_strlent(base);
	if (n >= len_base)
		ft_putnbr_basefd_one(n / len_base, base, fd, count);
	ft_putchar_fd_two(base[n % len_base], fd, count);
}

void	ft_putnbr_basefd_two(unsigned long long n, char *base, int fd,
		int *count)
{
	unsigned long long	base_len;

	base_len = ft_strlent(base);
	if (n >= base_len)
		ft_putnbr_basefd_two(n / base_len, base, fd, count);
	ft_putchar_fd_two(base[n % base_len], fd, count);
}
// int	ft_putchar(char c)
// {
// 	return (write(1, &c, 1));
// }

// int	ft_putstr(const char *s)
// {
// 	return(write(1, s, ft_strlent(s)));
// }

// void    ft_putnbr_base(int nbr, char *base)
// {
//     int base_size;

//     if (ft_check_base(base) == 1)
//         return ;
//     base_size = 0;
//     while (base[base_size])
//     {
//         base_size++;
//     }
//     if (nbr < 0)
//     {
//         ft_putchar('-');
//         ft_putchar(base[nbr / base_size]);
//     }
//     else
//     {
//         ft_putchar(base[nbr / base_size]);
//     }
// }

// int	ft_putnbr(int n)
// {
// 	int i;

// 	i = 0;
// 	if (n < 0)
// 	{
// 		i += ft_putchar('-');
// 		n -= n;
// 	}
// 	if (n >= 10)
// 	{
// 		i += ft_putnbr(n / 10);
// 	}
// 	i += ft_putchar('0' + n % 10);
// 	return (i);
// }

// int	ft_putnbr_hex_upper(unsigned int n)
// {
// 	const char *hx;

// 	hx = "0123456789ABCDEF";
// 	// if (n < 0)
// 	// 	ft_putnbr_hex_upper(n * -1);
// 	if (n >= 16)
// 	{
// 		ft_putnbr_hex_upper(n / 16);
// 		ft_putnbr_hex_upper(n % 16);
// 	}
// 	else
// 	{
// 		ft_putchar(hx[n]);
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_putnbr_hex_lower(unsigned long n)
// {
// 	const char *hx;

// 	hx = "0123456789abcdef";
// 	// if (n < 0)
// 	// 	ft_putnbr_hex_lower(n * -1);
// 	if (n >= 16)
// 	{
// 		ft_putnbr_hex_lower(n / 16);
// 		ft_putnbr_hex_lower(n % 16);
// 	}
// 	else
// 	{
// 		ft_putchar(hx[n]);
// 		return (1);
// 	}
// 	return (0);
// }

// int	ft_hdl_ptr(unsigned long ptr)
// {
// 	int	w_char;

// 	w_char = write(1, "0x", 2);
// 	w_char += ft_putnbr_hex(ptr, w_char);
// 	return (w_char);
// }

// int	ft_putnbr_unsigned(unsigned long num)
// {
// 	if (num == 0)
// 		return (ft_putchar('0'));
// 	else
// 		return (ft_putnbr(num));
// }

// int	ft_put_p(void *n)
// {
// 	int		count;
// 	char	hex;

// 	count = 0;
// 	hex = "0123456789abcdef";
// 	if (n < 16)
// 		count += ft_putchar(hex[n]);
// 	else
// 	{
// 		count += ft_put_p(n / 16);
// 		count += ft_put_p(n % 16);
// 	}
// 	return (count);
// }
