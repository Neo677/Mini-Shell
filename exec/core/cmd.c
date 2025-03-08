#include "../include/exec.h"

char	*error_execute_cmd(t_pipex *pipex, char *cmd)
{
	struct stat	path_stat;

	if (access(cmd, F_OK) == 0)
	{
		stat(cmd, &path_stat);
		if (S_ISDIR(path_stat.st_mode))
		{
			printf("bash: %s: Is a directory\n", cmd);
			free_error(pipex, 126);
		}
		else
			printf("bash: %s: No such file or directory\n", cmd);
	}
	else
	{
		if (ft_strchr_exec(cmd, '/') == 0)
			printf("bash: %s: No such file or directory\n", cmd);
		else
			printf("%s: command not found\n", cmd);
	}
	free_error(pipex, 127);
	return (NULL);
}

char	*find_cmd(t_pipex *pipex, char *cmd, char **paths)
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
	error_execute_cmd(pipex, cmd);
	return (NULL);
}

char	*find_path(t_pipex *pipex, char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (str_search(envp[i], "PATH", 4) == 0)
		i++;
	pipex->paths = ft_split_pipex(pipex, envp[i] + 5, ':');
	pipex->path_cmd = find_cmd(pipex, cmd, pipex->paths);
	return (pipex->path_cmd);
}

void	execute_cmd(t_pipex *pipex, char **arg, char **envp)
{
	pipex->path = find_path(pipex, arg[0], envp);
	if (execve(pipex->path, arg, envp) == -1)
	{
		if (ft_strcmp(arg[0], ".") == 0)
		{
			if (!arg[1])
			{
				printf(CMD_EXEC CMD_EXEC2);
				free_error(pipex, 2);
			}
			else
			{
				printf("%s: command not found\n", arg[0]);
				free_error(pipex, 127);
			}
		}
		else if (ft_strcmp(arg[0], "..") == 0)
		{
			printf("%s: command not found\n", arg[0]);
			free_error(pipex, 127);
		}
		printf("bash: %s: Is a directory\n", arg[0]);
		free_error(pipex, 126);
	}
}
