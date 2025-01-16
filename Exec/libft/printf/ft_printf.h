/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 02:08:31 by dpascal           #+#    #+#             */
/*   Updated: 2025/01/15 11:49:49 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

typedef struct s_data
{
	int	i;
	int	fd;
}		t_data;

int		ft_putchar(char c, int fd);
int		ft_putstr(char *s, int fd);
int		ft_p_adress(unsigned long p, int len, int fd);
int		ft_putnbr(int n, char *base, int len, int fd);
int		ft_uputnbr(unsigned int n, char *base, int len, int fd);
int		ft_putnbr_adr(unsigned long n, char *base, int len, int fd);
int		ft_written(const char *format, va_list args, int len, t_data *data);
int		ft_printf_fd(int fd, const char *format, ...);
int		ft_strlen(char *s);

#endif
