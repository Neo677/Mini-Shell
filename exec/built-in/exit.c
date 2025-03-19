/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:28 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/19 19:13:28 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	ft_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '-' || arg[i] == '+')
			i++;
		if (arg[i] >= '0' && arg[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

int	atol_sign(char *str, int i, int *sign)
{
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			*sign *= -1;
		}
		i++;
	}
	return (i);
}

long long	ft_atol(t_buit_in *exec, char *str, int *error)
{
	long long	res;
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	res = 0;
	if (ft_strcmp(str, "-9223372036854775808") == 0)
		return (-9223372036854775807 - 1);
	i = atol_sign(str, i, &sign);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	if (res < 0)
	{
		*error = 1;
		exec->status = 2;
		exec->exit_bh = 1;
		return (0);
	}
	return (res * sign);
}

int	error_ft_exit(t_buit_in *exec, char **tab)
{
	if (tab[2])
	{
		ft_printf_fd(2, "bash: exit: too many arguments\n");
		exec->exit_bh = 1;
		exec->status = 1;
		return (0);
	}
	if (ft_numeric(tab[1]) == 0)
	{
		ft_printf_fd(2, "bash: exit: %s: numeric argument required\n", tab[1]);
		exec->exit_bh = 1;
		exec->status = 2;
		return (0);
	}
	return (1);
}

int	ft_exit(t_buit_in *exec, char **tab)
{
	long long	num;
	int			error;

	num = 0;
	if (tab[1])
	{
		ft_printf_fd(1, "exit\n");
		if (error_ft_exit(exec, tab) == 0)
			return (0);
		error = 0;
		num = ft_atol(exec, tab[1], &error);
		if (error == 1)
			return (ft_printf_fd(2, EXIT_ERR, tab[1]), 0);
		if (num > 255 || num < 0)
		{
			num %= 256;
			if (num < 0)
				num += 256;
		}
		exec->exit_bh = 1;
		exec->status = num;
		return (num);
	}
	exec->exit_bh = 2;
	return (num);
}
