/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:19 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/13 10:59:54 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	check_built_in(char *str)
{
	if ((ft_strcmp(str, "env") == 0) || (ft_strcmp(str, "pwd") == 0)
		|| (ft_strcmp(str, "export") == 0) || (ft_strcmp(str, "unset") == 0)
		|| (ft_strcmp(str, "exit") == 0) || (ft_strcmp(str, "echo") == 0)
		|| (ft_strcmp(str, "cd") == 0))
	{
		return (1);
	}
	return (0);
}

int	execute_built_in(t_buit_in *exec, t_command *cmd)
{
	if (ft_strcmp(cmd->arg[0], "env") == 0)
		ft_env(&exec->env_cpy);
	else if (ft_strcmp(cmd->arg[0], "pwd") == 0)
		ft_pwd(&exec->env_cpy, exec->cd);
	else if (ft_strcmp(cmd->arg[0], "export") == 0)
		ft_export(exec, &exec->env_cpy, cmd->arg);
	else if (ft_strcmp(cmd->arg[0], "unset") == 0)
		ft_unset(exec, &exec->env_cpy, cmd->arg[1]);
	else if (ft_strcmp(cmd->arg[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd->arg[0], "exit") == 0)
		return (ft_exit(exec, cmd->arg));
	else if (ft_strcmp(cmd->arg[0], "cd") == 0)
		exec->cd = ft_cd(exec, &exec->env_cpy, cmd->arg);
	else
		printf("error : execute_built_in\n");
	return (0);
}
