/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:50 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/20 07:54:39 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	one_command(t_pipex *pipex, t_buit_in *exec, char **env, t_command *current)
{
	int	saved_stdout;
	int	saved_stdin;

	saved_stdout = dup(STDOUT_FILENO);
	saved_stdin = dup(STDIN_FILENO);
	if (change_dir(exec, current, pipex) == 1 || !(current->arg))
		return (1);
	exec->i = count_heredoc(exec, current);
	redir_input(exec, current, pipex);
	redir_output(exec, current, pipex);
	if (check_built_in(current->arg[0]) == 1)
		execute_built_in(exec, current);
	else
		no_built_in(pipex, exec, env, current);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdout);
	close(saved_stdin);
	free(pipex->pid);
	return (0);
}

int	child_process(t_pipex *pipex, t_buit_in *exec, char **env,
		t_command *current)
{
	if (change_dir(exec, current, pipex) == 1 || !(current->arg))
		exit(1);
	if (current->redirections && check_dir_in(current) != 0)
		redir_input(exec, current, pipex);
	else if (pipex->prev_pipe != -1)
	{
		dup2(pipex->prev_pipe, STDIN_FILENO);
		close(pipex->prev_pipe);
	}
	if (current->redirections && check_dir_out(current) != 0)
		redir_output(exec, current, pipex);
	else if (pipex->i < pipex->cmd_count - 1)
	{
		dup2(pipex->pipe_fd[1], STDOUT_FILENO);
		close(pipex->pipe_fd[1]);
	}
	close(pipex->pipe_fd[0]);
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
			return (perror("pipe"), exec->status = EXIT_FAILURE);
	}
	setup_signal_more(*current);
	exec->i = count_heredoc(exec, *current);
	pipex->pid[pipex->i] = fork();
	if (pipex->pid[pipex->i] < 0)
	{
		perror("fork");
		return (exec->status = EXIT_FAILURE);
	}
	if (pipex->pid[pipex->i] == 0)
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
		if (waitpid(pipex->pid[pipex->i], &pipex->status, 0) == -1)
			perror("waitpid");
		else if (WIFEXITED(pipex->status))
			exec->status = WEXITSTATUS(pipex->status);
		else if (WIFSIGNALED(pipex->status))
			exec->status = 128 + WTERMSIG(pipex->status);
		pipex->i++;
	}
	free(pipex->pid);
	return (exec->status);
}

void	process(t_pipex *pipex, t_command *cmd, t_buit_in *exec, t_env *env_cpy)
{
	t_command	*current;

	signal(SIGQUIT, signal_handler);
	signal(SIGINT, signal_handler2);
	current = cmd;
	if (init_process(pipex, cmd) != 0)
		return ;
	exec->i = -1;
	exec->status = 0;
	exec->env = change_t_env_to_tab(env_cpy);
	if (pipex->cmd_count == 1)
		one_command(pipex, exec, exec->env, current);
	else
		more_commands(pipex, current, exec, exec->env);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
