#include "../include/exec.h"

int	change_dir_in(t_buit_in *exec, t_redirections *current)
{
	int	infile;

	if (current->type == 2 && current->file)
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

int	change_dir_out(t_buit_in *exec, t_redirections *current)
{
	int	outfile;
	if ((current->type == 3 || current->type == 4) && current->file)
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

int	change_dir(t_buit_in *exec, t_command *cmd)
{
	t_redirections	*current;
	int				error;

	error = 0;
	current = cmd->redirections;
	while (current)
	{
		if (change_dir_in(exec, current) == EXIT_FAILURE)
			return (exec->status = EXIT_FAILURE);
		if (change_dir_out(exec, current) == EXIT_FAILURE)
			return (exec->status = EXIT_FAILURE);
		current = current->next;
	}
	if (error == 1)
		return (exec->status = EXIT_FAILURE);
	return (0);
}
