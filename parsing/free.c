/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:11:47 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:20:46 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *error)
{
	ft_printf_fd(STDERR_FILENO, "minishell: error exit detected %s\n", error);
	exit(EXIT_FAILURE);
}

void	ft_free_token(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head->next;
		free(head->value);
		free(head);
		head = tmp;
	}
}

void	ft_free_redirection(t_redirections *redir)
{
	t_redirections	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->file);
		free(redir);
		redir = tmp;
	}
}

void	ft_free_commande_lst(t_command *command)
{
	t_command	*tmp;
	int			i;

	while (command)
	{
		tmp = command->next;
		i = 0;
		if (command->arg)
		{
			while (command->arg[i])
			{
				free(command->arg[i]);
				i++;
			}
			free(command->arg);
		}
		ft_free_redirection(command->redirections);
		free(command);
		command = tmp;
	}
}

void	ft_main_free(t_command *cmd, t_redirections *redir, t_token *head)
{
	if (cmd)
		ft_free_commande_lst(cmd);
	if (redir)
		ft_free_redirection(redir);
	if (head)
		ft_free_token(head);
}
