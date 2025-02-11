#include "../include/pipex.h"

void	free_tab_pipex(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	free_all_pipex(t_pipex *pipex)
{
	if (pipex->cmd)
		free_tab_pipex(pipex->cmd);
	if (pipex->paths)
		free_tab_pipex(pipex->paths);
	if (pipex->path)
		free(pipex->path);
	if (pipex->pid)
		free(pipex->pid);
	if (access("temp_null", F_OK) == 0)
		unlink("temp_null");
	if (access("temp_null2", F_OK) == 0)
		unlink("temp_null2");
}

void	close_file(t_pipex *pipex)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
}

void	free_error(t_pipex *pipex, char *error, int key_error)
{
	free_all_pipex(pipex);
	close_file(pipex);
	ft_printf_fd(2, "%s", error);
	exit(key_error);
}
