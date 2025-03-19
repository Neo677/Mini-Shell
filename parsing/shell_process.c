/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:52:09 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/19 20:54:09 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_shell(t_buit_in *exec)
{
	pid_t	pid;
	int		status;
	char	*av[2];

	av[0] = "./minishell";
	av[1] = NULL;
	status = 0;
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	exec->env = change_t_env_to_tab(exec->env_cpy);
	pid = fork();
	if (pid == 0)
		execve("./minishell", av, exec->env);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			exec->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exec->status = 128 + WTERMSIG(status);
	}
	signal(SIGINT, signal_handler);
	return (exec->status);
}

int	ft_strcmp_shell(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!s1)
		return (1);
	while (s1[i] && s1[i] == ' ')
	{
		i++;
	}
	while (s2[j])
	{
		if (s1[i] != s2[j])
			return (s1[i] - s2[j]);
		i++;
		j++;
	}
	while (s1[i])
	{
		if (s1[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}
