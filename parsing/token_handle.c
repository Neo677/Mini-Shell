/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:12:07 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/04 17:12:08 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <string.h>

/*
                    🚨    🚨    🚨
    03/12/24
    here we gonna check if the token is ok with the rest of the str :
    and if its good we gonna add it :
    1) clear the space
    2) identify word
    3) identify Heredoc

    (at the begining i've got a main fonction for handle the token 
    (in the utils you can find the utils fonction for add the token to 
    the chain list), but i have to split in 3 fonction form the norm and also 
    it will make the code better to read)
    Utils for the lexer :
    the purpsoe of the fonction is to extract the quote at the begining and
    create a new node on the chain list or signal an error that mean is not closed  
    utility :
    1) detect a quote open et search for the closing
    2) if a quote close is missing, return (NULL)
    3) allocate memory dynamicilly to a chain list wo can 
        contain the str betwin the quote
        ex = input = "hello my name is tom"
                      0------------------\0
*/

int ft_is_redirection(t_token *token)
{
    if (token->type == TOKEN_IN ||
        token->type == TOKEN_OUT ||
        token->type == TOKEN_APPEND ||
        token->type == TOKEN_HEREDOC)
        return (1);
    return (0);
}

/*
    Here we gonna need to split this fonction in 3 way :
		1) handle the pipe error and use fonction in ft_validay_pipes
		2) handle redirection in or out (still use the tab op[3])
		3) also add the handle word in the main 

	At this moment we break into fragment the input of the user 
	and put it in the enum token (ex. TOKEN_PIPE, TOKEN_WORD, etc...)
*/

void ft_handle_operator(t_token **head, const char **input)
{
    char operateur[3];

    if (**input == '|') 			 // Gestion des pipes
    {
        if (*(*input + 1) == '|')	 // Double pipe (||)
        {
            ft_error_pipe("||");
            (*input) += 2;
            ft_free_token(*head);	 // Libère les tokens déjà créés
            *head = NULL;			 // Réinitialise la liste
            return;					 // Arrête immédiatement
        }
        (*input)++;
        ft_add_token(head, ft_create_token(TOKEN_PIPE, "|"));
    }
    else if (**input == '>' || **input == '<')  // Gestion des redirections (<, >, <<, >>)
    {
        operateur[0] = **input;
        operateur[1] = 0;
        (*input)++;
        if (**input == operateur[0]) 			// Double redirection (<< ou >>)
        {
            operateur[1] = **input;
            (*input)++;
        }
        if (!**input || **input == '|' || **input == '<' || **input == '>')
        {
            ft_error_redirections(operateur);
            ft_free_token(*head); 				// Libère les tokens créés
            *head = NULL; 						// Réinitialise la liste
            return; 							// Arrête immédiatement
        }
        ft_add_token(head, ft_create_token(ft_identify_token(operateur), operateur));
    }
}


void ft_handle_word(t_token **head, const char **input)
{
    char *token;

    token = ft_get_next_token(input);
    ft_add_token(head, ft_create_token(TOKEN_WORD, token));
}

/* Gestion des variables d'environnement */
int ft_handle_env_var(t_token **head, const char **input)
{
    char *env_var;

    env_var = ft_extract_env_var(input);
    if (!env_var) // Variable d'environnement mal formée
        return (1);
    ft_add_token(head, ft_create_token(TOKEN_ENV_VAR, env_var));
    return (0);
}
