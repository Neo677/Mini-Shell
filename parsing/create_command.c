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

int ft_create_command_lst(t_token *token, t_command **lst)
{
    t_command *current = NULL;
    const char *file;
    int redir_type;

    while (token)
    {
        if (token->type == TOKEN_PIPE)
        {
            current = ft_create_command(lst);
            if (!current)
            {
                ft_printf("[ERROR] Échec de création de commande\n");
                return (0);
            }
        }
        else if (token->type == TOKEN_WORD)
        {
            if (!current)
                current = ft_create_command(lst);
            if (!ft_add_arguments(current, token->value))
            {
                ft_printf("[ERROR] Impossible d'ajouter l'argument : %s\n", token->value);
                return (0);
            }
        }
        else if (ft_is_redirection(token))
        {
            if (!current)
                current = ft_create_command(lst);
            if (!token->next || token->next->type != TOKEN_WORD)
            {
                ft_printf("[ERROR] Redirection sans fichier ou argument valide\n");
                return (0);
            }
            file = token->next->value;
            redir_type = token->type;
            if (!ft_add_redirections(current, redir_type, file))
            {
                ft_printf("[ERROR] Impossible d'ajouter la redirection : %s\n", token->value);
                return (0);
            }
        }
        token = token->next;
    }
    return (1);
}
