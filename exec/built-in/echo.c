/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:19 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/19 11:27:22 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	check_option_echo(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
	{
		i++;
		if (!str[i])
			return (1);
		while (str[i])
		{
			if (str[i] != 'n' && str[i] != 'e')
				return (1);
			i++;
		}
	}
	else
		return (1);
	return (0);
}

void	print_echo(t_command *cmd, int i, int line_break)
{
	char	*str;

	while (cmd->arg[i])
	{
		str = remove_backslash(cmd->arg[i]);
		printf("%s", str);
		if (cmd->arg[i + 1])
			printf(" ");
		i++;
		free(str);
	}
	if (line_break <= 0)
		printf("\n");
}

void	ft_echo(t_command *cmd)
{
	int	i;
	int	line_break;

	i = 1;
	line_break = 0;
	if (!cmd->arg[1])
	{
		if (cmd->redirections)
			return ;
		write(1, "\n", 1);
		return ;
	}
	while (cmd->arg[i])
	{
		if (check_option_echo(cmd->arg[i]) == 0)
		{
			line_break = 1;
			i++;
		}
		else
			break ;
	}
	print_echo(cmd, i, line_break);
}
