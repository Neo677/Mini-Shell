#include "../include/exec.h"

int	check_redir_2(t_pipex *pipex, t_redirections *redirection, int in)
{
	if (redirection->type == 2)
	{
		pipex->infile = open(redirection->file, O_RDONLY, 0644);
		if (pipex->infile < 0)
		{
			perror(redirection->file);
			return (-1);
		}
		in = 1;
		dup2(pipex->infile, STDIN_FILENO);
		close(pipex->infile);
	}
	return (in);
}

int	check_dir_5(t_pipex *pipex, t_redirections *redirection, int in, int *i)
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
				return (-1);
			}
			in = 1;
			dup2(pipex->infile, STDIN_FILENO);
			close(pipex->infile);
			(*i)++;
		}
	}
	return (in);
}

int	redir_input(t_command *cmd, t_pipex *pipex)
{
	t_redirections	*redirection;
	int				i;
	int				in;

	i = 0;
	in = 0;
	redirection = cmd->redirections;
	if (!redirection)
		return (-1);
	while (redirection)
	{
		in = check_redir_2(pipex, redirection, in);
		if (in < 0)
			return (-1);
		in = check_dir_5(pipex, redirection, in, &i);
		if (in < 0)
			return (-1);
		redirection = redirection->next;
	}
	return (in);
}

int	check_n_change_out(t_pipex *pipex, t_redirections *dir, int out)
{
	if (dir->type == 3)
	{
		pipex->outfile = open(dir->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		if (pipex->outfile < 0)
		{
			perror(dir->file);
			return (-1);
		}
		out = 1;
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
	if (dir->type == 4)
	{
		pipex->outfile = open(dir->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		if (pipex->outfile < 0)
		{
			perror(dir->file);
			return (-1);
		}
		out = 1;
		dup2(pipex->outfile, STDOUT_FILENO);
		close(pipex->outfile);
	}
	return (out);
}

int	redir_output(t_command *cmd, t_pipex *pipex)
{
	t_redirections	*redirection;
	int				out;

	redirection = cmd->redirections;
	out = 0;
	if (!redirection)
		return (-1);
	while (redirection)
	{
		out = check_n_change_out(pipex, redirection, out);
		if (out < 0)
			return (-1);
		redirection = redirection->next;
	}
	return (out);
}
