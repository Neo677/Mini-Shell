

#include "../built-in/built_in.h"

void	redir_input(t_command *cmd, t_pipex *pipex)
{
	t_command *current;
	int	i;

	current = cmd;
	i = 0;
	while (current->redirections)
	{
		if (current->redirections->type == 2)
		{
			pipex->infile = open(current->redirections->file, O_RDONLY, 0644);
		}
		if (current->redirections->type == 3)
		{
			pipex->outfile = open(current->redirections->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		if (current->redirections->type == 4)
		{
			pipex->outfile = open(current->redirections->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
		}
		if (current->redirections->type == 5)
		{
			if (pipex->filename_hd && pipex->filename_hd[i])
				pipex->infile = open(pipex->filename_hd[i], O_CREAT | O_TRUNC | O_RDONLY, 0644);
			i++;
		}
		current->redirections = current->redirections->next;
	}
}

void	child_process(t_pipex *pipex, t_command *cmd, char **envp)
{
	int	i;
	int	pipe_fd[2];
	pid_t	pid;

	i = 0;
	while (i < count_cmd(cmd)) // - 1
	{
		if (i < count_cmd(cmd)) // - 1
			pipe(pipe_fd);
	
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return ;
		}
		if (pid == 0)
		{
			redir_input(cmd, pipex);
			if (pipex->infile >= 0)
			{
				dup2(pipex->infile, STDIN_FILENO);
				close (pipex->infile);
			}
			if (pipex->outfile >= 0)
			{
				dup2(pipex->outfile, STDOUT_FILENO);
				close (pipex->outfile);
			}
			else if (i < count_cmd(cmd)) // - 1
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (i > 0)
				dup2(pipe_fd[0], STDIN_FILENO);
			close (pipe_fd[0]);
			close (pipe_fd[1]);
			execute_cmd(pipex, cmd->arg, envp);
			// regrouper cmd->arg en une chaine pour envoyer au 2 eme arg de execute_cmd
		}
		close (pipe_fd[1]);
		if (i > 0)
			close (pipe_fd[0]);
		i++;
	}
	i = 0;
	while (i < count_cmd(cmd))
	{
		wait(NULL);
		i++;
	}
}
