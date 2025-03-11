#include "../include/exec.h"

int	one_command(t_pipex *pipex, t_buit_in *exec, char **env, t_command *current)
{
	if (check_built_in(current->arg[0]) == 1)
	{
		// redir_input(exec, current, pipex);
		redir_output(exec, current, pipex);
		if (check_file2(exec, current) == 1)
			return (1);
		execute_built_in(exec, current);
	}
	else
		return (no_built_in(pipex, exec, env, current));
	return (0);
}

int	child_process(t_pipex *pipex, t_buit_in *exec, char **env,
		t_command *current)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, signal_handler);
	if (redir_input(exec, current, pipex) == EXIT_FAILURE
		&& pipex->prev_pipe != -1)
	{
		dup2(pipex->prev_pipe, STDIN_FILENO);
		close(pipex->prev_pipe);
	}
	if (redir_output(exec, current, pipex) == EXIT_FAILURE
		&& pipex->i < pipex->cmd_count - 1)
	{
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
	}
	close(pipex->pipe_fd[0]);
	if (check_file2(exec, current) == 1)
		exit(1);
	if (check_built_in(current->arg[0]) == 1)
		execute_built_in(exec, current);
	else
		execute_cmd(exec, pipex, current->arg, env);
	exit(0);
}

int	while_commands(t_pipex *pipex, t_buit_in *exec, char **env,
		t_command **current)
{
	if (pipex->i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipe_fd) == -1)
		{
			perror("pipe");
			return (exec->status = EXIT_FAILURE);
		}
	}
	pipex->pid = fork();
	if (pipex->pid < 0)
	{
		perror("fork");
		return (exec->status = EXIT_FAILURE);
	}
	if (pipex->pid == 0)
		child_process(pipex, exec, env, *current);
	if (pipex->prev_pipe != -1)
		close(pipex->prev_pipe);
	if (pipex->i < pipex->cmd_count - 1)
		close(pipex->pipe_fd[1]);
	pipex->prev_pipe = pipex->pipe_fd[0];
	*current = (*current)->next;
	pipex->i++;
	return (1);
}

int	more_commands(t_pipex *pipex, t_command *current, t_buit_in *exec,
		char **env)
{
	while (pipex->i < pipex->cmd_count)
	{
		if (while_commands(pipex, exec, env, &current) == 0)
			return (2);
	}
	pipex->i = 0;
	while (pipex->i < pipex->cmd_count)
	{
		/*
			while (wait(&pipex->status) < 0)
				;
		*/
		wait(&pipex->status);
		if (WIFEXITED(pipex->status))
			exec->status = WEXITSTATUS(pipex->status);
		pipex->i++;
	}
	signal(SIGQUIT, SIG_IGN);
	return (exec->status);
}

void	process(t_pipex *pipex, t_command *cmd, t_buit_in *exec, char **env)
{
	t_command	*current;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler2);
	current = cmd;
	init_process(pipex, cmd);
	exec->status = 0;
	if (pipex->cmd_count == 1)
		one_command(pipex, exec, env, current);
	else
		more_commands(pipex, current, exec, env);
}
