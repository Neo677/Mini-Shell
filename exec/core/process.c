#include "../include/exec.h"

int	one_command(t_pipex *pipex, t_buit_in *exec, char **env, t_command *current)
{
	if (check_built_in(current->arg[0]) == 1)
	{
		redir_input(current, pipex);
		redir_output(current, pipex);
		execute_built_in(exec, current);
	}
	else
	{
		pipex->pid = fork();
		if (pipex->pid < 0)
			return (perror("fork"), 0);
		if (pipex->pid == 0)
		{
			signal(SIGQUIT, signal_handler);
			redir_input(current, pipex);
			redir_output(current, pipex);
			execute_cmd(pipex, current->arg, env);
		}
		wait(&pipex->status);
		if (WIFEXITED(pipex->status))
			return (WEXITSTATUS(pipex->status));
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, SIG_IGN);
	}
	return (0);
}

int	child_process(t_pipex *pipex, t_buit_in *exec, char **env,
		t_command *current)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, signal_handler);
	if (redir_input(current, pipex) != 1 && pipex->prev_pipe != -1)
	{
		dup2(pipex->prev_pipe, STDIN_FILENO);
		close(pipex->prev_pipe);
	}
	if (redir_output(current, pipex) != 1 && pipex->i < pipex->cmd_count - 1)
	{
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
	}
	close(pipex->pipe_fd[0]);
	if (check_built_in(current->arg[0]) == 1)
		execute_built_in(exec, current);
	else
		execute_cmd(pipex, current->arg, env);
	exit(0);
}

int	while_commands(t_pipex *pipex, t_buit_in *exec, char **env,
		t_command *current)
{
	if (pipex->i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipe_fd) == -1)
		{
			perror("pipe");
			return (0);
		}
	}
	pipex->pid = fork();
	if (pipex->pid < 0)
	{
		perror("fork");
		return (0);
	}
	if (pipex->pid == 0)
		child_process(pipex, exec, env, current);
	if (pipex->prev_pipe != -1)
		close(pipex->prev_pipe);
	if (pipex->i < pipex->cmd_count - 1)
		close(pipex->pipe_fd[1]);
	pipex->prev_pipe = pipex->pipe_fd[0];
	current = current->next;
	pipex->i++;
	return (1);
}

int	more_commands(t_pipex *pipex, t_command *current, t_buit_in *exec,
		char **env)
{
	while (pipex->i < pipex->cmd_count)
	{
		if (while_commands(pipex, exec, env, current) == 0)
			return (2);
	}
	pipex->i = 0;
	while (pipex->i < pipex->cmd_count)
	{
		wait(&pipex->status);
		if (WIFEXITED(pipex->status))
			return (WEXITSTATUS(pipex->status));
		pipex->i++;
	}
	signal(SIGQUIT, SIG_IGN);
	return (0);
}

int	process(t_pipex *pipex, t_command *cmd, t_buit_in *exec, char **env)
{
	t_command	*current;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler2);
	current = cmd;
	init_process(pipex, cmd);
	if (pipex->cmd_count == 1)
		return (one_command(pipex, exec, env, current));
	else
		return (more_commands(pipex, current, exec, env));
	return (0);
}

// int child_process(t_pipex *pipex, t_command *cmd, t_buit_in *exec,
	// char **env)
// {
// 	signal(SIGINT, SIG_IGN);
// 	signal(SIGQUIT, signal_handler);
// 	signal(SIGINT, signal_handler2);
// 	int	i;
// 	int	pipe_fd[2];
// 	int	prev_pipe;
// 	int	cmd_count;
// 	pid_t	pid;
// 	t_command	*current;
// 	int	status;

// 	i = 0;
// 	prev_pipe = -1;
// 	cmd_count = count_cmd(cmd);
// 	current = cmd;
// 	if (cmd_count == 1)
// 	{
// 		if (check_built_in(current->arg[0]) == 1)
// 		{
// 			redir_input(current, pipex);
// 			redir_output(current, pipex);
// 			execute_built_in(exec, current);
// 		}
// 		else
// 		{
// 			pid = fork();
// 			if (pid < 0)
// 			{
// 				perror("fork");
// 				return (0);
// 			}
// 			if (pid == 0)
// 			{
// 				signal(SIGQUIT, signal_handler);
// 				redir_input(current, pipex);
// 				redir_output(current, pipex);
// 				execute_cmd(pipex, current->arg, env);
// 			}
// 			wait(&status);
// 			if (WIFEXITED(status))
// 				return (WEXITSTATUS(status));
// 			signal(SIGQUIT, SIG_IGN);
// 			signal(SIGINT, SIG_IGN);
// 		}
// 	}
// 	else
// 	{
// 		while (i < cmd_count)
// 		{
// 			if (i < cmd_count - 1)
// 			{
// 				if (pipe(pipe_fd) == -1)
// 				{
// 					perror("pipe");
// 					return (0);
// 				}
// 			}
// 			pid = fork();
// 			if (pid < 0)
// 			{
// 				perror("fork");
// 				return (0);
// 			}
// 			if (pid == 0)
// 			{
// 				signal(SIGINT, SIG_DFL);
// 				signal(SIGQUIT, signal_handler);
// 				if (redir_input(current, pipex) != 1 && prev_pipe != -1)
// 				{
// 					dup2(prev_pipe, STDIN_FILENO);
// 					close(prev_pipe);
// 				}
// 				if (redir_output(current, pipex) != 1 && i < cmd_count - 1)
// 				{
// 					dup2(pipe_fd[1], STDOUT_FILENO);
// 					close(pipe_fd[1]);
// 				}
// 				close(pipe_fd[0]);
// 				if (check_built_in(current->arg[0]) == 1)
// 					execute_built_in(exec, current);
// 				else
// 					execute_cmd(pipex, current->arg, env);
// 				exit(0);
// 			}
// 			if (prev_pipe != -1)
// 				close(prev_pipe);
// 			if (i < cmd_count - 1)
// 				close(pipe_fd[1]);
// 			prev_pipe = pipe_fd[0];
// 			current = current->next;
// 			i++;
// 			}
// 			i = 0;
// 		while (i < cmd_count)
// 		{
// 			wait(&status);
// 			if (WIFEXITED(status))
// 				return (WEXITSTATUS(status));
// 			i++;
// 		}
// 		signal(SIGQUIT, SIG_IGN);
// 	}
// 	return (0);
// }
