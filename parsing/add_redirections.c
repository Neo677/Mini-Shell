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

static t_redirections	*create_redirection(int type, const char *file,
		t_parse_context *ctx)
{
	t_redirections	*redir;

	redir = malloc(sizeof(t_redirections));
	if (!redir)
	{
		ft_printf_fd(2, "minishell: allocation error\n");
		return (NULL);
	}
	redir->type = type;
	if (type == TOKEN_HEREDOC)
		redir->is_literal = 1;
	else
		redir->is_literal = 0;
	if (redir->is_literal)
		redir->file = ft_strdup_v2(file);
	else
		redir->file = ft_expand_variables(file, ctx);
	if (!redir->file)
	{
		ft_printf_fd(2, "minishell: memory allocation error\n");
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

int	ft_add_redirections_struct(t_command *cmd, int type, const char *file,
		t_parse_context *ctx)
{
	t_redirections	*new_redir;
	t_redirections	*current;

	if (!cmd || !file)
	{
		ft_printf_fd(2, "minishell: syntax error near token\n");
		return (0);
	}
	new_redir = create_redirection(type, file, ctx);
	if (!new_redir)
		return (0);
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
