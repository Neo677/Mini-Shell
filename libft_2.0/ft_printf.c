/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 10:47:33 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/16 10:47:36 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_p_adress_v2(unsigned long long ad_laurent, int fd, int *count)
{
	if (!ad_laurent)
		return (ft_putstr_fd_two("(nil)", fd, count));
	ft_putstr_fd_two("0x", 1, count);
	if (ad_laurent == -1ULL)
		return (ft_putstr_fd_two("ffffffffffffffff", fd, count));
	ft_putnbr_basefd_two(ad_laurent, "0123456789abcdef", fd, count);
}
// Donc, en combinant -1 avec ull,
// on indique que nous voulons un nombre unsigned long long
// qui est égal à -1.
// Mais puisque -1 n'est pas représentable directement en unsigned,

static void	ft_hdl_bro(const char **format, va_list arg, int fd, int *count)
{
	while (**format == '%')
	{
		(*format)++;
		if (**format == 'c')
			ft_putchar_fd_two(va_arg(arg, int), fd, count);
		else if (**format == 's')
			ft_putstr_fd_two(va_arg(arg, char *), fd, count);
		else if (**format == 'p')
			ft_p_adress_v2(va_arg(arg, unsigned long long), fd, count);
		else if (**format == 'd' || **format == 'i')
			ft_putnbr_basefd_one(va_arg(arg, int), "0123456789", fd, count);
		else if (**format == 'u')
			ft_putnbr_basefd_one(va_arg(arg, unsigned int), "0123456789", fd,
				count);
		else if (**format == 'x')
			ft_putnbr_basefd_two(va_arg(arg, unsigned int), "0123456789abcdef",
				fd, count);
		else if (**format == 'X')
			ft_putnbr_basefd_two(va_arg(arg, unsigned int), "0123456789ABCDEF",
				fd, count);
		else if (**format == '%')
			ft_putchar_fd_two('%', fd, count);
		(*format)++;
	}
}

/*
1er (*format)++;  Avance pour examiner le spécificateur suivant
else if (**format == '%')
	ft_putchar_fd_two('%', fd, count);
2eme(*format)++; Incrémente le pointeur pour éviter le double traitement du '%'
	return ; Termine cette itération pour éviter de répéter la sortie de '%'
3eme(*format)++; Incrémente le pointeur après avoir géré un spécificateur */

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	arg;

	va_start(arg, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
			ft_hdl_bro(&format, arg, STDOUT_FILENO, &count);
		else
		{
			ft_putchar_fd_two(*format, STDOUT_FILENO, &count);
			format++;
		}
	}
	va_end(arg);
	return (count);
}

/* if (*format == '%')
ft_hdl_bro(&format, arg, STDOUT_FILENO, &count); Gère le spécificateur
else
ft_putchar_fd_two(*format, STDOUT_FILENO, &count);
Imprime le caractère et incrémente ensuite

STDOUT_FILENO est utilisé pour référencer
la sortie standard dans les appels système de bas niveau,
comme write ou dup2. */

/* int	main(void)
{
	char			test_c0;
	char			test_c1;
	char			test_c2;

	char			*test_s0;
	char			*test_s1;
	char			*test_s2;

	void			*test_p;

	int				test_d0;
	int				test_d1;
	int				test_d2;

	int				test_i0;
	int				test_i1;
	int				test_i2;

	unsigned int	test_u0;
	unsigned int	test_u1;
	unsigned int	test_u2;

	unsigned int	test_x;
	unsigned int	test_X;
	unsigned int	test_x_min;
	unsigned int	test_X_min;

	test_c0 = 'a';
	test_c1 = 'b';
	test_c2 = 'c';

	test_s0 = "ABCDefgh";
	test_s1 = "abcdEFGH";
	test_s2 = "abcdefghijklmnopqrstuvwxy";

	test_p = "0123456789";

	test_d0 = 123456789;
	test_d1 = 123456789;
	test_d2 = 123456789;

	test_i0 = 123456789;
	test_i1 = 123456789;
	test_i2 = 123456789;

	test_u0 = 123456789;
	test_u1 = 123456789;
	test_u2 = 123456789;

	test_x = 01234567;
	test_X = 01234567;
	test_x_min = -1;
	test_X_min = -1;

	ft_printf("	mine :	%%, %% \n");
	printf("	real : 	%%, %% \n");
	ft_printf("my printf = test 1 caractere : %c,\n", test_c0);
	ft_printf("my printf = test 2 caractere : %c, %c\n", test_c0, test_c1);
	ft_printf("my printf = test 3 caractere : %c, %c, %c\n", test_c0, test_c1,
		test_c2);
	ft_printf("\n");
	ft_printf("my printf = test string 1 : 			%s\n", test_s0);
	ft_printf("my printf = test string 2 : 			%s, %s\n", test_s0,
					test_s1);
	ft_printf("my printf = test string 3 : 			%s, %s, %s\n", test_s0,
					test_s1, test_s2);
	ft_printf("\n");
	ft_printf("my printf = value pointeur : 			0123456789\n");
	ft_printf("my printf = test pointeur : 			%p\n", test_p);
	ft_printf("\n");
	ft_printf("my printf = test decimal 1: 			%d\n", test_d0);
	ft_printf("my printf = test decimal 2: 			%d, %d\n", test_d0,
					test_d1);
	ft_printf("my printf = test decimal 3: 			%d, %d, %d\n", test_d0,
					test_d1, test_d2);
	ft_printf("\n");
	ft_printf("my printf = test integer 1: 			%i\n", test_i0);
	ft_printf("my printf = test integer 2: 			%i, %i\n", test_i0,
					test_i1);
	ft_printf("my printf = test integer 3: 			%i, %i, %i\n", test_i0,
					test_i1, test_i2);
	ft_printf("\n");
	ft_printf("my printf = test unsigned decimal :		%u\n", test_u0);
	ft_printf("my printf = test unsigned decimal :		%u, %u\n", test_u0,
				test_u1);
	ft_printf("my printf = test unsigned decimal :		%u, %u, %u\n", test_u0,
				test_u1, test_u2);
	ft_printf("\n");
	ft_printf("my printf = value uns_lower : 			123456\n");
	ft_printf("my printf = test hexadecimal lower : 		%x\n", test_x);
	ft_printf("my printf = value uns_upper : 			123456\n");
	ft_printf("my printf = test hexadecimal upper :		%X\n", test_X);
	ft_printf("my printf = value uns_lower : 			-1\n");
	ft_printf("my printf = test hexadecimal lower : 		%x\n", test_x_min);
	ft_printf("my printf = value uns_upper : 			-1\n");
	ft_printf("my printf = test hexadecimal upper :		%X\n", test_X_min);
	ft_printf("my printf = test pourcent 			%%\n");
	ft_printf("-------------------------------------------------------------\n");
	printf("real printf = test 1 caractere : %c,\n", test_c0);
	printf("real printf = test 2 caractere : %c, %c\n", test_c0, test_c1);
	printf("real printf = test 3 caractere : %c, %c, %c\n", test_c0, test_c1,
		test_c2);
	printf("\n");
	printf("real printf = test string 1 : 			%s\n", test_s0);
	printf("real printf = test string 2 : 			%s, %s\n", test_s0,
					test_s1);
	printf("real printf = test string 3 : 			%s, %s, %s\n", test_s0,
					test_s1, test_s2);
	printf("\n");
	printf("real printf = value pointeur : 			0123456789\n");
	printf("real printf = test pointeur : 			%p\n", test_p);
	printf("\n");
	printf("real printf = test decimal 1: 			%d\n", test_d0);
	printf("real printf = test decimal 2: 			%d, %d\n", test_d0,
					test_d1);
	printf("real printf = test decimal 3: 			%d, %d, %d\n", test_d0,
					test_d1, test_d2);
	printf("\n");
	printf("real printf = test integer 1: 			%i\n", test_i0);
	printf("real printf = test integer 2: 			%i, %i\n", test_i0,
					test_i1);
	printf("real printf = test integer 3: 			%i, %i, %i\n", test_i0,
					test_i1, test_i2);
	printf("\n");
	printf("real printf = test unsigned decimal :		%u\n", test_u0);
	printf("real printf = test unsigned decimal :		%u, %u\n", test_u0,
				test_u1);
	printf("real printf = test unsigned decimal :		%u, %u, %u\n", test_u0,
				test_u1, test_u2);
	printf("\n");
	printf("real printf = value uns_lower : 		123456\n");
	printf("real printf = test hexadecimal lower : 		%x\n", test_x);
	printf("real printf = value uns_upper : 		123456\n");
	printf("real printf = test hexadecimal upper :		%X\n", test_X);
	printf("real printf = value uns_lower : 		-1\n");
	printf("real printf = test hexadecimal lower : 		%x\n", test_x_min);
	printf("real printf = value uns_upper : 		-1\n");
	printf("real printf = test hexadecimal upper :		%X\n", test_X_min);
	printf("real printf = test pourcent 			%%\n");
} */
