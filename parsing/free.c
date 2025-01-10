/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:11:47 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/04 17:11:48 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *error)
{
	ft_printf("[🚨ERROR🚨] minishell = %s\n", error);
	exit(EXIT_FAILURE);
}


void	ft_free_token(t_token *head)
{
	t_token	*tmp;

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
	int	i;

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

void	ft_free_split(t_token *head, t_command *cmd_lst)
{
	ft_printf("[ERROR] Token invalid !\n");
	ft_free_token(head);
	head = NULL;
	ft_free_commande_lst(cmd_lst);
	return;
}