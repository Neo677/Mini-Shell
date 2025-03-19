/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:36 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/14 17:51:12 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (pipex->pid)
		free(pipex->pid);
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
