/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:40 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/18 14:41:52 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

extern int	g_signal;

void	signal_handler3(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
		close(STDIN_FILENO);
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
	}
}

void	while_hd(t_pipex *pipex, t_token *current, int heredoc_fd)
{
	int		saved_stdin;
	char	*line;

	signal(SIGINT, signal_handler3);
	saved_stdin = dup(STDIN_FILENO);
	g_signal = 0;
	while (1)
	{
		pipex->line_hd++;
		line = readline(">");
		if (g_signal == 130)
		{
			if (line)
				free(line);
			break ;
		}
		if (end_while_hd(pipex, current, heredoc_fd, line) == 1)
			return ;
	}
	dup2(saved_stdin, STDIN_FILENO);
	close(saved_stdin);
}

void	process_heredoc_token(t_buit_in *exec, t_pipex *pipex, t_token *current,
		int *i)
{
	pid_t	pid;
	int		heredoc_fd;
	char	*filename;

	filename = heredoc_name(*i);
	if (access(filename, F_OK) == 0)
		unlink(filename);
	heredoc_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	pid = fork();
	if (pid == 0)
	{
		while_hd(pipex, current, heredoc_fd);
		close(heredoc_fd);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	exec->status = g_signal;
	pipex->filename_hd[*i] = ft_strdup(filename);
	(*i)++;
	free(filename);
}

void	set_while_hd(t_buit_in *exec, t_pipex *pipex, t_token *current)
{
	int	i;

	i = 0;
	while (current)
	{
		if (current->type == 5)
		{
			if (current->next && current->next->type == 0)
				process_heredoc_token(exec, pipex, current, &i);
			if (g_signal == 130)
			{
				pipex->filename_hd[i] = NULL;
				break ;
			}
		}
		current = current->next;
	}
}

int	check_heredoc(t_buit_in *exec, t_token *token, t_pipex *pipex)
{
	t_token	*current;

	signal(SIGINT, SIG_IGN);
	current = token;
	init_hd(token, pipex);
	set_while_hd(exec, pipex, current);
	signal(SIGINT, signal_handler);
	return (0);
}
