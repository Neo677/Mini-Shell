/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:27 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:24:29 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_create_command(t_command **lst)
{
	t_command	*new;
	t_command	*last;

	new = malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->arg = NULL;
	new->redirections = NULL;
	new->next = NULL;
	if (*lst)
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	else
		lst = &new;
	return (new);
}

void	ft_create_command_lst(t_token *token, t_command **lst)
{
	const char	*file;
	t_command	*current;
	int			redir_type;

	current = NULL;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			current = ft_create_command(lst);
		else if (token->type == TOKEN_WORD)
		{
			if (!current)
				current = ft_create_command(lst);
			if (!ft_add_arguments(current, token->value))
				printf("[ERROR] cant add args : %s\n", token->value);
		}
		else if (ft_is_redirection(token))
		{
			if (!current)
				current = ft_create_command(lst);
			if (!token->next || token->next->type != TOKEN_WORD)
				printf("[ERROR] redirection sans fichier ou argument valide\n");
			file = token->next->value;
			redir_type = token->type;
			if (!ft_add_redirections(current, redir_type, file))
				printf("[ERROR] cant add the redirec : %s\n", token->value);
		}
		token = token->next;
	}
}
