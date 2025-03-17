/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:42:54 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/17 07:59:19 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	check_slash(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	error_file(t_buit_in *exec, t_pipex *pipex, char *cmd)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	if (access(cmd, F_OK) == 0 && check_slash(cmd, '/') == 0)
	{
		ft_printf_fd(2, "%s: command not found\n", cmd);
		free_error(pipex, exec->status = 127);
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(2, "bash: %s: Is a directory\n", cmd);
		free_error(pipex, exec->status = 126);
	}
}

void	error_access(t_buit_in *exec, t_pipex *pipex, char *cmd)
{
	error_file(exec, pipex, cmd);
	if (access(cmd, X_OK) != 0)
	{
		if (access(cmd, R_OK) == 0 && access(cmd, W_OK) == 0)
			ft_printf_fd(2, "%s: command not found\n", cmd);
		else
		{
			ft_printf_fd(2, "bash: %s: Permission denied\n", cmd);
			free_error(pipex, exec->status = 126);
		}
	}
	else
	{
		ft_printf_fd(2, "bash: %s: No such file or directory\n", cmd);
		exec->status = 1;
	}
}

char	*error_execute_cmd(t_buit_in *exec, t_pipex *pipex, char *cmd)
{
	if (access(cmd, F_OK) == 0)
		error_access(exec, pipex, cmd);
	else
	{
		if (ft_strchr_exec(cmd, '/') == 0)
			ft_printf_fd(2, "bash: %s: No such file or directory\n", cmd);
		else
			ft_printf_fd(2, "%s: command not found\n", cmd);
	}
	free_error(pipex, exec->status = 127);
	return (NULL);
}

void	err_execve(t_buit_in *exec, t_pipex *pipex, char **arg)
{
	if (ft_strcmp(arg[0], ".") == 0)
	{
		if (!arg[1])
		{
			ft_printf_fd(2, CMD_EXEC CMD_EXEC2);
			free_error(pipex, exec->status = 2);
		}
		else
		{
			ft_printf_fd(2, "%s: command not found\n", arg[0]);
			free_error(pipex, exec->status = 127);
		}
	}
	else if (ft_strcmp(arg[0], "..") == 0 || ft_strchr_exec(arg[0], '/') != 0)
	{
		ft_printf_fd(2, "%s: command not found\n", arg[0]);
		free_error(pipex, exec->status = 127);
	}
	ft_printf_fd(2, "bash: %s: Is a directory\n", arg[0]);
	free_error(pipex, exec->status = 126);
}
