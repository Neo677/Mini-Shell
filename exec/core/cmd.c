/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:32 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:48:33 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	error_access(t_buit_in *exec, t_pipex *pipex, char *cmd)
{
	struct stat	path_stat;

	stat(cmd, &path_stat);
	if (S_ISDIR(path_stat.st_mode))
	{
		ft_printf_fd(2, "bash: %s: Is a directory\n", cmd);
		free_error(pipex, exec->status = 126);
	}
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

char	*find_cmd(t_buit_in *exec, t_pipex *pipex, char *cmd, char **paths)
{
	int	i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		pipex->paths_cmd = malloc(sizeof(char) * ft_strlen_pipex(cmd)
				+ ft_strlen_pipex(pipex->paths[i]) + 2);
		if (!pipex->paths_cmd)
			free_error(pipex, 0);
		ft_strcpy(pipex->paths_cmd, paths[i]);
		ft_strcat(pipex->paths_cmd, "/");
		ft_strcat(pipex->paths_cmd, cmd);
		if (access(pipex->paths_cmd, X_OK) == 0)
			return (pipex->paths_cmd);
		free(pipex->paths_cmd);
		i++;
	}
	error_execute_cmd(exec, pipex, cmd);
	return (NULL);
}

char	*find_path(t_buit_in *exec, t_pipex *pipex, char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (str_search(envp[i], "PATH", 4) == 0)
		i++;
	pipex->paths = ft_split_pipex(pipex, envp[i] + 5, ':');
	pipex->path_cmd = find_cmd(exec, pipex, cmd, pipex->paths);
	return (pipex->path_cmd);
}

void	execute_cmd(t_buit_in *exec, t_pipex *pipex, char **arg, char **envp)
{
	pipex->path = find_path(exec, pipex, arg[0], envp);
	if (execve(pipex->path, arg, envp) == -1)
	{
		if (ft_strcmp(arg[0], ".") == 0)
		{
			if (!arg[1])
			{
				ft_printf_fd(2, CMD_EXEC CMD_EXEC2);
				free_error(pipex, 2);
			}
			else
			{
				ft_printf_fd(2, "%s: command not found\n", arg[0]);
				free_error(pipex, exec->status = 127);
			}
		}
		else if (ft_strcmp(arg[0], "..") == 0 || ft_strchr_exec(arg[0],
				'/') != 0)
		{
			ft_printf_fd(2, "%s: command not found\n", arg[0]);
			free_error(pipex, exec->status = 127);
		}
		ft_printf_fd(2, "bash: %s: Is a directory\n", arg[0]);
		free_error(pipex, exec->status = 126);
	}
}
