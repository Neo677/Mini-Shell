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

//         handle the case if in input there is == "" or ''
char *ft_handle_quote(char **input, char quote)
{
    const char  *start;
    char        *token;

    start = ++(*input);
    while (**input && **input != quote)
    {
        (*input)++;
    }
    if (*input == quote)
    {
        token = ft_strndup(start, *input - start);
        (*input)++; // skip la fermeture de la quote 
    }
    return (NULL); // quote non fermée
}

void    ft_handle_operator(t_token **head, const char **input)
{
    char op[3];

    op[0] = **input;
    (*input)++;
    op[1] = '\0';
    if ((**input == '>' || **input == '<') && op[0] == **input)
    {
        op[1] = **input;
        (*input)++;
    }
    op[2] = '\0';
    ft_add_token(head, ft_create_token(ft_identify_token(op), ft_strdup(op)));
}

void ft_handle_word(t_token **head, const char **input)
{
    char *token;

    token = ft_get_next_token(input);
    ft_add_token(head, ft_create_token(TOKEN_WORD, token));
}





