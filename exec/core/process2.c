/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:54 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:48:55 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	no_built_in(t_pipex *pipex, t_buit_in *exec, char **env, t_command *current)
{
	pipex->pid = fork();
	if (pipex->pid < 0)
		return (perror("fork"), 0);
	if (pipex->pid == 0)
	{
		signal(SIGQUIT, signal_handler);
		execute_cmd(exec, pipex, current->arg, env);
	}
	wait(&pipex->status);
	if (WIFEXITED(pipex->status))
		return (exec->status = WEXITSTATUS(pipex->status));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (0);
}
