

#include "../include/pipex.h"

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












// void	ft_pid(t_pipex *pipex, t_command *cmd, char **envp)
// {
// 	int	i;

// 	i = 0;
// 	pipex->pid = malloc(sizeof(int) * pipex->len);
// 	if (!pipex->pid)
// 		return (-1);
	
// }