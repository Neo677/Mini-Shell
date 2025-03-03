#include "../include/exec.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	free_all_core(t_pipex *pipex)
{
	if (pipex->paths)
		free_tab(pipex->paths);
	if (pipex->path)
		free(pipex->path);
}

void	close_file(t_pipex *pipex)
{
	if (pipex->infile >= 0)
		close(pipex->infile);
	if (pipex->outfile >= 0)
		close(pipex->outfile);
}

void	free_error(t_pipex *pipex, int key_error)
{
	free_all_core(pipex);
	close_file(pipex);
	exit(key_error);
}
