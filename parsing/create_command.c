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

/*
  Creates a new command and adds it to the end of the command list.
 
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

t_command *ft_create_command(t_command **lst)
{
    t_command *new_cmd;
    t_command *last;

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

/*
    1) PIPE = if we meet a pipe, on go to the next command
    2) WORD = 
        A) if there is not current command we creat it
        B) and add the word as an arguments
    3) REDIRECTION = 
        A) if there is not current command we creat it
        B) check if the next token is a word
        C) sotck the file name 
        D) add the redirections to a struct
        E) advance of 2 token
            1 = (<, >, <<, >>)
            2 = the word it follow (filename)
    4) ELSE no recognizes the token
*/

int ft_create_command_lst(t_token *token, t_command **lst)
{
    t_command *current;
    const char *file;

    current = NULL;
    while (token)
    {
        if (token->type == TOKEN_PIPE)
        {
            if (current)
                current->p_pipe = 1;
            current = NULL;
            token = token->next;
            continue;
        }
        else if (token->type == TOKEN_WORD)
        {
            if (!current)
                current = ft_create_command(lst);
            if (!current || !ft_add_arguments(current, token->value))
                return (ft_printf("[DEBUG] failed to add arguments = %s\n", token->value), free(current), 0);
            token = token->next;
        }
        else if (ft_is_redirection(token))
        {
            if (!current)
                current = ft_create_command(lst);
            if (!current || !token->next || token->next->type != TOKEN_WORD)
                return (ft_printf("[DEBUG] redirection without valid arguments = %s\n", token->value), free(current), 0);
            file = token->next->value;
            if (!ft_add_redirections_struct(current, token->type, file))
                return (ft_printf("[DEBUG] failed to add redirections = %s\n", token->value), free(current), 0);
            token = token->next->next;
        }
        else if (token->type == TOKEN_ENV_VAR)
        {
            if (!current)
                current = ft_create_command(lst);
            if (!current || !ft_add_arguments(current, token->value))
                return (ft_printf("[DEBUG] failed to add env var = %s\n", token->value), free(current), 0);
            token = token->next;
        }
        else
            return (ft_printf("[DEBUG] Unexpected token type = %d\n", token->type), 0);
    }
    return (1);
}


//              old V.
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
//             continue;
//         }
//         else if (token->type == TOKEN_WORD)
//         {
//             if (!current)
//                 current = ft_create_command(lst);
//             if (!current || !ft_add_arguments(current, token->value))
//             {
//                 ft_free_command(current);
//                 return (ft_printf("[DEBUG] failed to add arguments = %s\n", token->value), 0);
//             }
//             token = token->next;
//         }
//         else if (ft_is_redirection(token))
//         {
//             if (!current)
//                 current = ft_create_command(lst);
//             if (!current || !token->next || token->next->type != TOKEN_WORD)
//             {
//                 ft_free_command(current);
//                 return (ft_printf("[DEBUG] redirection without valid arguments = %s\n", token->value), 0);
//             }
//             file = token->next->value;
//             if (!ft_add_redirections_struct(current, token->type, file))
//             {
//                 ft_free_command(current);
//                 return (ft_printf("[DEBUG] failed to add redirections = %s\n", token->value), 0);
//             }
//             token = token->next->next;
//         }
//         else if (token->type == TOKEN_ENV_VAR)
//         {
//             if (!current)
//                 current = ft_create_command(lst);
//             if (!current || !ft_add_arguments(current, token->value))
//             {
//                 ft_free_command(current);
//                 return (ft_printf("[DEBUG] failed to add env var = %s\n", token->value), 0);
//             }
//             token = token->next;
//         }
//         else
//         {
//             ft_free_command(current);
//             return (ft_printf("[DEBUG] Unexpected token type = %d\n", token->type), 0);
//         }
//     }
//     return (1);
// }

