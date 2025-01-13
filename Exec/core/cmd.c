
#include "pipex.h"

char	*find_cmd(t_pipex *pipex, char *cmd, char **paths)
{
	int	i;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		pipex->paths_cmd = malloc(sizeof(char) * ft_strlen(cmd)
				+ ft_strlen(pipex->paths[i]) + 2);
		if (!pipex->paths_cmd)
			free_error(pipex, "Erreur allocation paths_cmd", 0);
		ft_strcpy(pipex->paths_cmd, paths[i]);
		ft_strcat(pipex->paths_cmd, "/");
		ft_strcat(pipex->paths_cmd, cmd);
		if (access(pipex->paths_cmd, X_OK) == 0)
			return (pipex->paths_cmd);
		free(pipex->paths_cmd);
		i++;
	}
	if (pipex->error != 1 && access("temp_null", F_OK) != 0)
		write_error(cmd);
	free_error(pipex, "", 127);
	return (NULL);
}

char	*find_path(t_pipex *pipex, char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (str_search(envp[i], "PATH", 4) == 0)
		i++;
	pipex->paths = ft_split(pipex, envp[i] + 5, ':');
	pipex->path_cmd = find_cmd(pipex, cmd, pipex->paths);
	return (pipex->path_cmd);
}

void	execute_cmd(t_pipex *pipex, char *argv, char **envp)
{
	pipex->cmd = ft_split(pipex, argv, ' ');
	pipex->path = find_path(pipex, pipex->cmd[0], envp);
	if (access("temp_null", F_OK) == 0)
		unlink("temp_null");
	if (access("temp_null2", F_OK) == 0)
		unlink("temp_null2");
	if (execve(pipex->path, pipex->cmd, envp) == -1)
		free_error(pipex, "", 0);
}
