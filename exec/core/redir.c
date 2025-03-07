#include "../include/exec.h"

void	check_redir_2(t_buit_in *exec, t_pipex *pipex,
		t_redirections *redirection)
{
	if (redirection->type == 2)
	{
		pipex->infile = open(redirection->file, O_RDONLY, 0644);
		if (pipex->infile < 0)
		{
			exec->status = EXIT_FAILURE;
			return ;
		}
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
	}
}

void	check_dir_5(t_buit_in *exec, t_pipex *pipex,
		t_redirections *redirection, int *i)
{
	if (redirection->type == 5)
	{
		if (pipex->filename_hd && pipex->filename_hd[*i])
		{
			pipex->infile = open(pipex->filename_hd[*i], O_CREAT | O_RDONLY,
					0644);
			if (pipex->infile < 0)
			{
				perror(pipex->filename_hd[*i]);
				exec->status = EXIT_FAILURE;
				return ;
			}
			dup2(pipex->infile, STDIN_FILENO);
			close(pipex->infile);
			(*i)++;
		}
	}
}

int	redir_input(t_buit_in *exec, t_command *cmd, t_pipex *pipex)
{
	t_redirections	*redirection;
	int				i;

	i = 0;
	redirection = cmd->redirections;
	if (!redirection)
		return (EXIT_FAILURE);
	while (redirection)
	{
		check_redir_2(exec, pipex, redirection);
		if (exec->status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		check_dir_5(exec, pipex, redirection, &i);
		if (exec->status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redirection = redirection->next;
	}
	return (exec->status);
}

void	check_n_change_out(t_buit_in *exec, t_pipex *pipex, t_redirections *dir)
{
	if (dir->type == 3)
	{
		pipex->outfile = open(dir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (pipex->outfile < 0)
		{
			exec->status = EXIT_FAILURE;
			return ;
		}
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
	if (dir->type == 4)
	{
		pipex->outfile = open(dir->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (pipex->outfile < 0)
		{
			exec->status = EXIT_FAILURE;
			return ;
		}
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
}

int	redir_output(t_buit_in *exec, t_command *cmd, t_pipex *pipex)
{
	t_redirections	*redirection;

	redirection = cmd->redirections;
	if (!redirection)
		return (EXIT_FAILURE);
	while (redirection)
	{
		check_n_change_out(exec, pipex, redirection);
		if (exec->status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		redirection = redirection->next;
	}
	return (exec->status);
}
