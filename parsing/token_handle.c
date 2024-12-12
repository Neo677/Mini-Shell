/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:12:07 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/04 17:12:08 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

*/

/*
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
char *ft_handle_quote(const char **input, char quote)
{
    const char  *start;

    (*input)++;
    start = *input;
    while (**input && **input != quote)
        (*input)++;
    if (**input != quote || **input == '\0')
    {
        ft_error_quote();
        return (NULL);
    }
    (*input)++;
    return (ft_strndup(start, *input - start - 1));
}

int ft_is_redirection(t_token *token)
{
    if (token->type == TOKEN_IN ||
        token->type == TOKEN_OUT ||
        token->type == TOKEN_APPEND ||
        token->type == TOKEN_HEREDOC)
        return (1);
    return (0);
}

//                      problem we need to check if the input is == ">" we need to return an error

/*
    here we gonna need to split this fonction in 3 way 
    1) handle the pipe error and use fonction in ft_validay_pipes
    2) handle redirection in or out (still use the tab op[3])
    3) also add the handle word in the main 
        handle fonction
C’est à ce moment que chaque fragment de l’entrée utilisateur est classé en un type de token (ex. TOKEN_PIPE, TOKEN_WORD, etc.).
*/

void ft_handle_operator(t_token **head, const char **input)
{
    char operateur[3]; // pourquoi 3 

    if (**input == '|')
    {
        if (*(*input + 1 ) == '|')
        {
            ft_error_pipe("||");
            (*input) += 2;
            return;
        }
        (*input)++;
        ft_add_token(head, ft_create_token(TOKEN_PIPE, "|"));
    }
    else if (**input == '>' || **input == '<')
    {
        operateur[0] = **input; // ex : input = < 
        operateur[1] = 0;
        operateur[2] = 0;
        (*input)++;
        if (**input == operateur[0]) // si input [0] == < es ce que input[1] = < 
        {
            operateur[1] = **input; // input = <<
            (*input)++;
        }
        if (**input == operateur[0])
        {
            ft_error_redirections(operateur);
            while (**input == operateur[0]) // ex input = <<<<<<<<<<<<<< on passe tout
                (*input)++;
            ft_add_token(head, ft_create_token(TOKEN_ERROR, "invalid redirections"));
            return;
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

void    ft_handle_env_var(t_token **head, const char **input)
{
    char *env_var;

    env_var = ft_extract_env_var(input);
    if (!env_var)
        return;
    ft_add_token(head, ft_create_token(TOKEN_ENV_VAR, env_var));
}