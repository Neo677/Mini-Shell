/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:54 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/20 07:54:51 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	no_built_in(t_pipex *pipex, t_buit_in *exec, char **env, t_command *current)
{
	pipex->pid[0] = fork();
	if (pipex->pid[0] < 0)
		return (perror("fork"), 0);
	if (pipex->pid[0] == 0)
	{
		signal(SIGQUIT, signal_handler);
		execute_cmd(exec, pipex, current->arg, env);
	}
	if (waitpid(pipex->pid[0], &pipex->status, 0) == -1)
	{
		perror("waitpid");
		return (0);
	}
	if (WIFEXITED(pipex->status))
		exec->status = WEXITSTATUS(pipex->status);
	else if (WIFSIGNALED(pipex->status))
		exec->status = 128 + WTERMSIG(pipex->status);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (0);
}

int	count_t_env(t_env *env_cpy)
{
	t_env	*current;
	int		i;

	current = env_cpy;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**change_t_env_to_tab(t_env *env_cpy)
{
	t_env	*current;
	char	**tab;
	char	*temp;
	int		i;

	current = env_cpy;
	tab = malloc(sizeof(char *) * (count_t_env(env_cpy) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (current)
	{
		temp = ft_strjoin(current->key, "=");
		tab[i] = ft_strjoin(temp, current->value);
		free(temp);
		i++;
		current = current->next;
	}
	tab[i] = NULL;
	return (tab);
}

int	count_heredoc(t_buit_in *exec, t_command *current)
{
	t_redirections	*redirection;

	redirection = current->redirections;
	if (!redirection)
		return (0);
	while (redirection)
	{
		if (redirection->type == 5)
			exec->i++;
		redirection = redirection->next;
	}
	return (exec->i);
}

void	setup_signal_more(t_command *current)
{
	if (ft_strcmp(current->arg[0], "more") == 0)
	{
		signal(SIGQUIT, signal_handler4);
		signal(SIGINT, signal_handler4);
	}
}
