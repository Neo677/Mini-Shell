#include "../include/exec.h"

int	check_file_in(t_buit_in *exec, t_token *token)
{
	int	infile;

	if (token->type == 2 && token->next->type == 0)
	{
		if (access(token->next->value, F_OK) != 0)
		{
			// ft_printf_fd(2, "bash: %s: 1No such file or directory\n", token->next->value);
			return (exec->status = EXIT_FAILURE);
		}
		if (access(token->next->value, R_OK) != 0)
		{
			// ft_printf_fd(2, "bash: %s: Permission denied\n", token->next->value);
			return (exec->status = EXIT_FAILURE);
		}
		infile = open(token->next->value, O_RDONLY, 0644);
		if (infile < 0)
		{
			// ft_printf_fd(2, "bash: ");
			// perror(token->next->value);
			return (exec->status = EXIT_FAILURE);
		}
		close (infile);
	}
	return (exec->status);
}

int	check_file_out(t_buit_in *exec, t_token *token)
{
	int	outfile;

	if ((token->type == 3 || token->type == 4) && token->next->type == 0)
	{
		if (access(token->next->value, W_OK) != 0 && access(token->next->value, F_OK) == 0)
		{
			// ft_printf_fd(2, "bash: %s: Permission denied\n", token->next->value);
			return (exec->status = EXIT_FAILURE);
		}
		outfile = open(token->next->value, O_TRUNC | O_CREAT | O_WRONLY,
				0644);
		if (outfile < 0)
		{
			// ft_printf_fd(2, "bash: ");
			// perror(token->next->value);
			return (exec->status = EXIT_FAILURE);
		}
		close (outfile);
	}
	return (exec->status);
}

int	check_file(t_buit_in *exec, t_token *token)
{
	int	error;

	error = 0;
	while (token)
	{
		if (check_file_in(exec, token) == EXIT_FAILURE)
			error = 1;
		if (check_file_out(exec, token) == EXIT_FAILURE)
			error = 1;
		token = token->next;
	}
	if (error == 1)
		return (exec->status = EXIT_FAILURE);
	return (exec->status);
}
