#include "../include/exec.h"

int	check_file_in(t_buit_in *exec, t_token *token)
{
	int	infile;

	if (token->type == 2)
	{
		if (token->next->type == 0)
		{
			infile = open(token->next->value, O_RDONLY, 0644);
			if (infile < 0)
			{
				ft_printf_fd(2, "bash: ");
				perror(token->next->value);
				return (exec->status = EXIT_FAILURE);
			}
		}
	}
	return (exec->status);
}

int	check_file_out(t_buit_in *exec, t_token *token)
{
	int	outfile;

	if (token->type == 3)
	{
		if (token->next->type == 0)
		{
			outfile = open(token->next->value, O_TRUNC | O_CREAT | O_WRONLY,
					0644);
			if (outfile < 0)
			{
				ft_printf_fd(2, "bash: ");
				perror(token->next->value);
				return (exec->status = EXIT_FAILURE);
			}
		}
	}
	return (exec->status);
}

int	check_file(t_buit_in *exec, t_token *token)
{
	while (token)
	{
		if (check_file_in(exec, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if (check_file_out(exec, token) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		token = token->next;
	}
	return (exec->status);
}
