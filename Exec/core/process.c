

#include "../built-in/built_in.h"

// void	ft_wait(t_pipex *pipex, int pid[], int len)
// {
// 	int	i;

// 	i = 0;
// 	while (i < len)
// 	{
// 		waitpid(pid[i], &pipex->status, 0);
// 		i++;
// 	}
// }

// void	ft_process(t_pipex *pipex, char **arg, char **envp, int i)
// {
// 	if (pipex->pid[i] == 0)
// 	{
// 		if (i != 0)
// 			pipex->error = 0;
// 		dup2(pipex->stdin_fd, STDIN_FILENO);
// 		if (i == pipex->len - 1)
// 			dup2(pipex->outfile, STDOUT_FILENO);
// 		else
// 			dup2(pipex->pipefd[1], STDOUT_FILENO);
// 		if (i < pipex->len - 1)
// 		{
// 			close(pipex->pipefd[0]);
// 			close(pipex->pipefd[1]);
// 		}
// 		execute_cmd(pipex, arg[i], envp);
// 	}
// }

// void	ft_pid(t_pipex *pipex, char **arg, char **envp)
// {
// 	pipex->pid = malloc(sizeof(int) * pipex->len);
// 	if (!pipex->pid)
// 		free_error(pipex, "Error : allocation pid", 0);
// 	pipex->stdin_fd = pipex->infile;
// 	while (pipex->i < pipex->len)
// 	{
// 		if (pipex->i < (pipex->len - 1))
// 			if (pipe(pipex->pipefd) < 0)
// 				free_error(pipex, "Error : pipefd", 0);
// 		pipex->pid[pipex->i] = fork();
// 		if (pipex->pid[pipex->i] < 0)
// 			free_error(pipex, "Error : pid", 0);
// 		ft_process(pipex, arg, envp, pipex->i);
// 		close(pipex->stdin_fd);
// 		if (pipex->i < pipex->len - 1)
// 		{
// 			close(pipex->pipefd[1]);
// 			pipex->stdin_fd = pipex->pipefd[0];
// 		}
// 		pipex->i++;
// 	}
// 	ft_wait(pipex, pipex->pid, pipex->len);
// }




void	ft_wait(t_pipex *pipex, int pid[], int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		waitpid(pid[i], &pipex->status, 0);
		i++;
	}
}

void	ft_process(t_pipex *pipex, t_command *cmd, char **envp, int i)
{
	if (pipex->pid[i] == 0)
	{
		dup2(pipex->stdin_fd, STDIN_FILENO);
		if (i == pipex->len - 1)
			dup2(pipex->outfile, STDOUT_FILENO);
		else
			dup2(pipex->pipefd[1], STDOUT_FILENO);
		if (i < pipex->len - 1)
		{
			close(pipex->pipefd[0]);
			close(pipex->pipefd[1]);
		}
		execute_cmd(pipex, cmd->arg[i], envp);
	}
}

void	ft_pid(t_pipex *pipex, t_command *cmd, char **envp)
{
	int	i;

	i = 0;
	pipex->pid = malloc(sizeof(int) * pipex->len);
	if (!pipex->pid)
		free_error(pipex, "Error : allocation pid", 0);
	pipex->stdin_fd = pipex->infile;
	while (i < pipex->len)
	{
		if (i < (pipex->len - 1))
			if (pipe(pipex->pipefd) < 0)
				free_error(pipex, "Error : pipefd", 0);
		pipex->pid[i] = fork();
		if (pipex->pid[i] < 0)
			free_error(pipex, "Error : pid", 0);
		ft_process(pipex, cmd, envp, i);
		close(pipex->infile);
		if (i < pipex->len - 1)
		{
			close(pipex->pipefd[1]);
			pipex->infile = pipex->pipefd[0];
		}
		i++;
	}
	ft_wait(pipex, pipex->pid, pipex->len);
}


void	redir_input(t_command *cmd, t_pipex *pipex)
{
	t_command *current;
	int i;

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
			{
				pipex->infile = open(pipex->filename_hd[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
			}
			i++;
		}
		current->redirections = current->redirections->next;
	}
}

void	child_process(t_pipex *pipex, t_command *cmd, char **envp)
{
	int i;
	int pipe_fd[2];
	pid_t pid;

	i = 0;
	while (i < count_cmd(cmd) - 1)
	{
		if (i < count_cmd(cmd) - 1)
			pipe(pipe_fd);
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			return;
		}
		if (pid == 0)
		{
			redir_input(cmd, pipex);
			if (pipex->infile >= 0)
			{
				dup2(pipex->infile, STDIN_FILENO);
				close(pipex->infile);
			}
			if (pipex->outfile >= 0)
			{
				dup2(pipex->outfile, STDOUT_FILENO);
				close(pipex->outfile);
			}
			else if (i < count_cmd(cmd) - 1)
				dup2(pipe_fd[1], STDOUT_FILENO);
			if (i > 0)
				dup2(pipe_fd[0], STDIN_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
			execute_cmd(pipex, cmd->arg[i], envp);
		}
		close(pipe_fd[1]);
		if (i > 0)
			close (pipe_fd[0]);
		i++;
	}
	i = 0;
	while (i < count_cmd(cmd))
	{
		wait (NULL);
		i++;
	}
}
