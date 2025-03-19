/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:25:57 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/06 13:05:02 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_av_envp(char **av, char **envp)
{
	av[0] = "/bin/sh";
	av[1] = "-c";
	av[2] = "echo $PPID";
	av[3] = NULL;
	envp[0] = NULL;
}

static void	ft_exec_child(char **av, char **envp, int fd_pipe[2])
{
	close(fd_pipe[0]);
	dup2(fd_pipe[1], STDOUT_FILENO);
	close(fd_pipe[1]);
	execve("/bin/sh", av, envp);
	exit(EXIT_FAILURE);
}

void	ft_fork_pid(char **av, char **envp, int *fd_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_exec_child(av, envp, fd_pipe);
	close(fd_pipe[1]);
	waitpid(pid, NULL, 0);
}

char	*ft_get_pid_str(void)
{
	char	*av[4];
	char	*envp[1];
	int		fd_pipe[2];
	char	buffer[32];
	int		nread;

	ft_init_av_envp(av, envp);
	if (pipe(fd_pipe) == -1)
		return (ft_strdup("0"));
	ft_fork_pid(av, envp, fd_pipe);
	nread = read(fd_pipe[0], buffer, sizeof(buffer) - 1);
	close(fd_pipe[0]);
	if (nread <= 0)
		return (ft_strdup("0"));
	buffer[nread] = '\0';
	if (buffer[nread - 1] == '\n')
		buffer[nread - 1] = '\0';
	return (ft_strdup(buffer));
}
