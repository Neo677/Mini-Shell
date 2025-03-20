/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:01:18 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/20 10:37:28 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

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
		ft_memset(pipex->filename_hd, 0, sizeof(char *) * (i + 1));
	}
	else
		pipex->filename_hd = NULL;
}

int	end_while_hd(t_pipex *pipex, t_token *current, int heredoc_fd, char *line)
{
	if (line == NULL)
	{
		ft_printf_fd(2, HD_1 HD_2, pipex->line_hd, current->next->value);
		free(line);
		return (1);
	}
	if (ft_strcmp(line, current->next->value) == 0)
	{
		free(line);
		return (1);
	}
	write(heredoc_fd, line, ft_strlen_dp(line));
	write(heredoc_fd, "\n", 1);
	free(line);
	return (0);
}

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
