/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:32 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/20 07:56:17 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char	*find_cmd(t_buit_in *exec, t_pipex *pipex, char *cmd, char **paths)
{
	int			i;
	struct stat	path_stat;

	i = 0;
	stat(cmd, &path_stat);
	if (access(cmd, X_OK) == 0 && !(S_ISDIR(path_stat.st_mode)))
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

char	*find_path(t_buit_in *exec, t_pipex *pipex, char *cmd, char **env)
{
	int	i;

	i = 0;
	while (env[i] && str_search(env[i], "PATH", 4) == 0)
		i++;
	if (env[i] == NULL)
	{
		ft_printf_fd(2, PATH_1 PATH_2, cmd);
		free_error(pipex, exec->status = 127);
	}
	pipex->paths = ft_split_pipex(pipex, env[i] + 5, ':');
	pipex->path_cmd = find_cmd(exec, pipex, cmd, pipex->paths);
	return (pipex->path_cmd);
}

void	execute_cmd(t_buit_in *exec, t_pipex *pipex, char **arg, char **env)
{
	if (ft_strcmp(arg[0], "./minishell") == 0)
	{
		if (arg[1])
			ft_printf_fd(2, "%s: command not found\n", arg[1]);
		free_error(pipex, exec->status = 127);
	}
	pipex->path = find_path(exec, pipex, arg[0], env);
	if (execve(pipex->path, arg, env) == -1)
		err_execve(exec, pipex, arg);
}
