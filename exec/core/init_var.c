/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:45 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:48:46 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	init_var(t_pipex *pipex)
{
	pipex->infile = dup(STDIN_FILENO);
	pipex->outfile = dup(STDOUT_FILENO);
	pipex->pipe_fd[0] = 0;
	pipex->pipe_fd[1] = 0;
	pipex->pid = 0;
	pipex->i = 0;
	pipex->status = 0;
	pipex->paths = NULL;
	pipex->path = NULL;
	pipex->paths_cmd = NULL;
	pipex->path_cmd = NULL;
	pipex->filename_hd = NULL;
	pipex->line_hd = 0;
}

void	init_process(t_pipex *pipex, t_command *cmd)
{
	pipex->infile = dup(STDIN_FILENO);
	pipex->outfile = dup(STDOUT_FILENO);
	pipex->one_cmd = 0;
	pipex->i = 0;
	pipex->prev_pipe = -1;
	pipex->cmd_count = count_cmd(cmd);
	pipex->status = 0;
	pipex->pipe_fd[0] = 0;
	pipex->pipe_fd[1] = 0;
	pipex->pid = 0;
	pipex->paths = NULL;
	pipex->path = NULL;
	pipex->paths_cmd = NULL;
	pipex->path_cmd = NULL;
}
