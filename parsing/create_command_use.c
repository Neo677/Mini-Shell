/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command_use.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:16:10 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:16:11 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_redirections(t_redirections *redir)
{
	t_redirections	*tmp;

	while (redir)
	{
		tmp = redir;
		redir = redir->next;
		free(tmp->file);
		free(tmp);
	}
}

void	ft_free_array(char **av)
{
	int	i;

	i = 0;
	if (!*av || !av)
		return ;
	while (av[i])
	{
		free(av[i]);
		i++;
	}
	free(av);
}

void	ft_free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->arg)
	{
		ft_free_array(cmd->arg);
	}
	if (cmd->redirections)
	{
		ft_free_redirections(cmd->redirections);
	}
	free(cmd);
}

void	ft_free_command_list(t_command **lst)
{
	t_command	*tmp;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		ft_free_command(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
