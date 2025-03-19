/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:25 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/18 18:04:12 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	change_dir_in(t_buit_in *exec, t_redirections *current)
{
	int	infile;

	if ((current->type == 2) && current->file)
	{
		if (access(current->file, F_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: No such file or directory\n",
				current->file);
			return (exec->status = EXIT_FAILURE);
		}
		if (access(current->file, R_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: Permission denied\n", current->file);
			return (exec->status = EXIT_FAILURE);
		}
		infile = open(current->file, O_RDONLY, 0644);
		if (infile < 0)
		{
			ft_printf_fd(2, "bash: ");
			perror(current->file);
			return (exec->status = EXIT_FAILURE);
		}
		close(infile);
	}
	return (0);
}

int	change_dir_out_3(t_buit_in *exec, t_redirections *current)
{
	int	outfile;

	if (current->type == 3 && current->file)
	{
		outfile = open(current->file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		if (outfile < 0)
		{
			ft_printf_fd(2, "bash: ");
			perror(current->file);
			return (exec->status = EXIT_FAILURE);
		}
		if (access(current->file, F_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: No such file or directory\n",
				current->file);
			return (exec->status = EXIT_FAILURE);
		}
		if (access(current->file, W_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: Permission denied\n", current->file);
			return (exec->status = EXIT_FAILURE);
		}
		close(outfile);
	}
	return (0);
}

int	change_dir_out_4(t_buit_in *exec, t_redirections *current)
{
	int	outfile;

	if (current->type == 4 && current->file)
	{
		outfile = open(current->file, O_APPEND | O_CREAT | O_WRONLY, 0644);
		if (outfile < 0)
		{
			ft_printf_fd(2, "bash: ");
			perror(current->file);
			return (exec->status = EXIT_FAILURE);
		}
		if (access(current->file, F_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: No such file or directory\n",
				current->file);
			return (exec->status = EXIT_FAILURE);
		}
		if (access(current->file, W_OK) != 0)
		{
			ft_printf_fd(2, "bash: %s: Permission denied\n", current->file);
			return (exec->status = EXIT_FAILURE);
		}
		close(outfile);
	}
	return (0);
}

int	change_dir(t_buit_in *exec, t_command *cmd, t_pipex *pipex)
{
	t_redirections	*current;

	current = cmd->redirections;
	while (current)
	{
		if (change_dir_in(exec, current) == EXIT_FAILURE)
			return (free(pipex->pid), exec->status = EXIT_FAILURE);
		if (change_dir_out_3(exec, current) == EXIT_FAILURE)
			return (free(pipex->pid), exec->status = EXIT_FAILURE);
		if (change_dir_out_4(exec, current) == EXIT_FAILURE)
			return (free(pipex->pid), exec->status = EXIT_FAILURE);
		current = current->next;
	}
	return (0);
}
