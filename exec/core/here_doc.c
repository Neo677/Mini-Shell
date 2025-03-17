/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:40 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/17 10:22:44 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char	*heredoc_name(int i)
{
	char	*name;
	char	*num;
	char	*filename;

	name = "/tmp/heredoc_";
	num = ft_itoa_exec(i);
	filename = malloc(sizeof(char) * (ft_strlen_dp(name) + ft_strlen_dp(num)
				+ 1));
	if (!filename)
	{
		free(num);
		return (NULL);
	}
	ft_strcpy(filename, name);
	ft_strcat(filename, num);
	free(num);
	return (filename);
}

void	init_hd(t_token *token, t_pipex *pipex)
{
	t_token	*current;
	int		i;

	current = token;
	i = 0;
	while (current)
	{
		if (current->type == 5 && current->next->type == 0)
			i++;
		current = current->next;
	}
	if (i > 0)
	{
		pipex->filename_hd = malloc(sizeof(char *) * (i + 1));
		if (!pipex->filename_hd)
			return ;
		pipex->filename_hd[i] = NULL;
	}
	else
		pipex->filename_hd = NULL;
}

void	while_hd(t_pipex *pipex, t_token *current, int heredoc_fd)
{
	char	*line;

	while (1)
	{
		pipex->line_hd++;
		line = readline(">");
		if (line == NULL)
		{
			ft_printf_fd(2, HD_1 HD_2, pipex->line_hd, current->next->value);
			free(line);
			return ;
		}
		if (ft_strcmp(line, current->next->value) == 0)
		{
			free(line);
			return ;
		}
		write(heredoc_fd, line, ft_strlen_dp(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
}

void	set_while_hd(t_pipex *pipex, t_token *current)
{
	int		heredoc_fd;
	char	*filename;
	int		i;

	i = 0;
	while (current)
	{
		if (current->type == 5)
		{
			if (current->next->type == 0)
			{
				filename = heredoc_name(i);
				if (access(filename, F_OK) == 0)
					unlink(filename);
				heredoc_fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
				while_hd(pipex, current, heredoc_fd);
				close(heredoc_fd);
				pipex->filename_hd[i] = ft_strdup(filename);
				i++;
				free(filename);
			}
		}
		current = current->next;
	}
}

int	check_heredoc(t_token *token, t_pipex *pipex)
{
	t_token	*current;

	current = token;
	init_hd(token, pipex);
	set_while_hd(pipex, current);
	return (0);
}
