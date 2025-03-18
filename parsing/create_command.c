/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:27 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:18:54 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
  Creates a new command and adds it to the end ∫bof the command list.

  1) Allocates memory for a new command.
  2) Initializes the new command's fields:
		A) arg = NULL
		B) redirections = NULL
		C) p_pipe = 0
		D) next = NULL
  3) If the command list is not empty:
		A) Traverse to the end of the list.
		B) Add the new command to the end of the list.
  4) If the command list is empty:
		A) Set the new command as the first command in the list.
 */

t_command	*ft_init_command(t_command **lst)
{
	t_command	*new_cmd;
	t_command	*last;

	new_cmd = malloc(sizeof(t_command));
	if (!new_cmd)
		return (NULL);
	new_cmd->arg = NULL;
	new_cmd->redirections = NULL;
	new_cmd->p_pipe = 0;
	new_cmd->next = NULL;
	if (*lst)
	{
		last = *lst;
		while (last->next)
			last = last->next;
		last->next = new_cmd;
	}
	else
		*lst = new_cmd;
	return (new_cmd);
}

int	ft_create_command_lst(t_token *token, t_command **lst, t_parse_context *ctx)
{
	t_command	*current;

	current = NULL;
	while (token)
	{
		if (token->type == TOKEN_PIPE)
			ft_create_cmd_pipe(&current);
		else if (token->type == TOKEN_ENV_VAR)
			ft_create_cmd_env(&current, token, lst);
		else if (ft_is_redirection(token))
		{
			ft_create_cmd_redirect(&current, token, lst, ctx);
			token = token->next;
			if (token)
				token = token->next;
			continue ;
		}
		else if (token->type == TOKEN_WORD)
			ft_create_cmd_word(&current, token, lst);
		else
			return (ft_free_command_list(lst), 0);
		token = token->next;
	}
	return (1);
}

// int ft_create_command_lst(t_token *token, t_command **lst)
// {
//     t_command *current;
//     const char *file;

//     current = NULL;
//     while (token)
//     {
//         if (token->type == TOKEN_PIPE)
//         {
//             if (current)
//                 current->p_pipe = 1;
//             current = NULL;
//             token = token->next;
//             continue ;
//         }
//         else if (token->type == TOKEN_WORD)
//         {
//             if (!current && !(current = ft_init_command(lst)))
//                 return (ft_free_command_list(lst), 0);
//             if (!ft_add_arguments(current, token->value))
//                 return (ft_free_command_list(lst), 0);
//             token = token->next;
//         }
//         else if (ft_is_redirection(token))
//         {
//             if (!current && !(current = ft_init_command(lst)))
//             {
//                 ft_free_command_list(lst);
//                 return (258);
//             }
//             if (!token->next || token->next->type != TOKEN_WORD)
//             {
//                 ft_printf_fd(STDERR_FILENO,
// "minishell: syntax error near redirection\n");
//                 ft_free_command_list(lst);
//                 return (258);
//             }
//             file = token->next->value;
//             if (!ft_add_redirections_struct(current, token->type, file))
//             {
//                 ft_printf_fd(STDERR_FILENO,
// "minishell: syntax error near unexpected token\n");
//                 ft_free_command_list(lst);
//                 return (258);
//             }
//             token = token->next->next;
//         }
//         else if (token->type == TOKEN_ENV_VAR)
//         {
//             if (!current && !(current = ft_init_command(lst)))
//             {
//                 ft_free_command_list(lst);
//                 return (258);
//             }
//             if (!ft_add_arguments(current, token->value))
//             {
//                 ft_printf_fd(STDERR_FILENO,
// "minishell: failed to add envrionnement varibles as arugments\n");
//                 ft_free_command_list(lst);
//                 return (258);
//             }
//             token = token->next;
//         }
//         else
//         {
//             ft_printf_fd(STDERR_FILENO,
// "minishell: syntax error near unexpected token '%s'\n", token->value);
//             return (ft_free_command_list(lst), 0);
//         }
//     }
//     return (1);
// }
