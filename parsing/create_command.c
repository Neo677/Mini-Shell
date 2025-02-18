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

// t_command *ft_init_command(t_command **lst)
// {
//     t_command *new_cmd;
//     t_command *last;

//     new_cmd = malloc(sizeof(t_command));
//     if (!new_cmd)
//     {
//         ft_printf_fd(STDERR_FILENO, "minishell: memory failed for t_command\n");
//         return (NULL);
//     }
//     new_cmd->arg = NULL;
//     new_cmd->redirections = NULL;
//     new_cmd->p_pipe = 0;
//     new_cmd->next = NULL;
//     if (*lst)
//     {
//         last = *lst;
//         while (last->next)
//             last = last->next;
//         last->next = new_cmd;
//     }
//     else
//         *lst = new_cmd;
//     return (new_cmd);
// }

// int ft_create_command_lst(t_token *token, t_command **lst)
// {
//     t_command *current;
//     const char *file;
//     int ret;

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
//             if (!current && !(current = ft_init_command(lst)))
//                 return (258);
//             if (!ft_add_arguments(current, token->value))
//             {
//                 ft_printf_fd(STDERR_FILENO, "minishell: failed to add argument\n");
//                 return (258);
//             }
//             token = token->next;
//         }
//         else if (ft_is_redirection(token))
//         {
//             if (!current && !(current = ft_init_command(lst)))
//                 return (258);
//             if (!token->next || token->next->type != TOKEN_WORD)
//             {
//                 ft_printf_fd(STDERR_FILENO, "minishell: syntax error near redirection\n");
//                 return (258);
//             }
//             file = token->next->value;
//             if (!ft_add_redirections_struct(current, token->type, file))
//             {
//                 ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");
//                 return (258);
//             }
//             token = token->next->next;
//         }


//         else if (token->type == TOKEN_ENV_VAR)
//         {
//             if (!current && !(current = ft_init_command(lst)))
//                 return (258);
//             if (!ft_add_arguments(current, token->value))
//             {
//                 ft_printf_fd(STDERR_FILENO, "minishell: failed to add envrionnement varibles as arugments\n");
//                 return (258);
//             }
//             token = token->next;
//         }
//         else
//         {
//             ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token '%s'\n", token->value);
//             return (258);
//         }
//     }
//     return (1);
// } 


// Add these at the top of the file
static void	ft_free_redirections(t_redirections *redir)
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

void    ft_free_array(char **av)
{
    int i = 0;

    if (!*av || !av)
        return;
    while (av[i])
    {
        free(av[i]);
        i++;
    }
    free(av);
}

static void	ft_free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->arg)
	{
		ft_free_array(cmd->arg);  // Assuming this exists to free char **
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

t_command *ft_init_command(t_command **lst)
{
    t_command *new_cmd;
    t_command *last;

    new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: memory failed for t_command\n");
        return (NULL);
    }
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
            if (!current && !(current = ft_init_command(lst)))
            {
                ft_free_command_list(lst);
                return (258);
            }
            if (!ft_add_arguments(current, token->value))
            {
                ft_printf_fd(STDERR_FILENO, "minishell: failed to add argument\n");
                ft_free_command_list(lst);
                return (258);
            }
            token = token->next;
        }
        else if (ft_is_redirection(token))
        {
            if (!current && !(current = ft_init_command(lst)))
            {
                ft_free_command_list(lst);
                return (258);
            }
            if (!token->next || token->next->type != TOKEN_WORD)
            {
                ft_printf_fd(STDERR_FILENO, "minishell: syntax error near redirection\n");
                ft_free_command_list(lst);
                return (258);
            }
            file = token->next->value;
            if (!ft_add_redirections_struct(current, token->type, file))
            {
                ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");
                ft_free_command_list(lst);
                return (258);
            }
            token = token->next->next;
        }
        else if (token->type == TOKEN_ENV_VAR)
        {
            if (!current && !(current = ft_init_command(lst)))
            {
                ft_free_command_list(lst);
                return (258);
            }
            if (!ft_add_arguments(current, token->value))
            {
                ft_printf_fd(STDERR_FILENO, "minishell: failed to add envrionnement varibles as arugments\n");
                ft_free_command_list(lst);
                return (258);
            }
            token = token->next;
        }
        else
        {
            ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token '%s'\n", token->value);
            ft_free_command_list(lst);
            return (258);
        }
    }
    return (1);
}