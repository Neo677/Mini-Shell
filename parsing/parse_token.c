/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:08 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:09 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
                    🚨    🚨    🚨
            07/12/24
    Now that I have finished taking an input / 
                                splitting it / 
                                checking every character / 
                                setting it in an enum struct 
    for reference so the parser can recognize the command.
    Now I can add the arguments, redirections, and pipe in a cmd struct.
                        ⛓️⛓️⛓️
    1) Create an empty command 
    2) Handle allocation errors (leak safe)
    3) Mark the command that contains a pipe
    4) Stop parsing to let a pipe handle the following commands
    5) Add a redirection to the command
    6) Free
    7) Add an argument to the command
    8) Free
*/

t_token *ft_parse_token(const char *input, t_env **env_cpy)
{
    t_token *token;
    t_command *cmd_lst;
    
    cmd_lst = NULL;
    token = NULL;
    if (!(input) || !(*input))
    {
        //return(ft_printf("[ERROR] Entrée vide\n"), NULL);
        return (NULL);
    }
    if (!ft_split_token(&token, input, env_cpy))
    {
        fprintf(stderr, "Error: Failed to split tokens\n");
        return (NULL);
    }
    // ft_print_tokens(token); // optionnal (LEXER part)
    if (!ft_create_command_lst(token, &cmd_lst))
    {
        fprintf(stderr, "Error: Failed to create command list\n");
        ft_free_commande_lst(cmd_lst);
        return (NULL);
    }
    // ft_print_command_lst(cmd_lst);
    return (token); // Retourne les tokens si tout est valide
}
