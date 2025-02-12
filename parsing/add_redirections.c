/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:23 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:24:24 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
                    🚨    🚨    🚨
    here we need to add a 'redirection' in a struct command
    the command is compose in 2️⃣parts :
             A)  type        B)      value
    A = the type of redirections (TOKEN_IN TOKEN OUT etc...)
    B = the value of (nom de fichier, delim de Heredoc, etc...)

    we can do a fonction gonna return a Boolean response for check
    if is in capacity of doing that :

    Be ready we gonna do :
    1) check parametre
    2) take memory for the specified file
    3) initialise the rediction (leak safe)
    4) add the redirections to the chain list of redirection
    5) return a true (1) 
*/

int	ft_add_redirections_struct(t_command *cmd, int type, const char *file)
{
	t_redirections	*new_redir;
	t_redirections	*current;

	if (!cmd || !file)
		return(ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n"), 0);
	new_redir = malloc(sizeof(t_redirections));
	if (!new_redir)
		return (ft_printf_fd(STDERR_FILENO, "minishell: allocation error\n"), 0);
	new_redir->type = type;
	new_redir->file = ft_strdup_v2(file);
	if (!new_redir->file)
		return(ft_printf_fd(STDERR_FILENO, "minishell: memory allocation error\n"), 0);
	new_redir->next = NULL;
	if (!cmd->redirections)
		cmd->redirections = new_redir;
	else
	{
		current = cmd->redirections;
		while (current->next)
			current = current->next;
		current->next = new_redir;
	}
	return (1);
}
