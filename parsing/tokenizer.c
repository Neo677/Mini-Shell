<<<<<<< Updated upstream

=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:57:08 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/04 15:57:09 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
>>>>>>> Stashed changes

#include "minishell.h"

/*
    fonction for take a token from the input :
        1) check if this is pipe
        2) check if this is < 
        3) check if this is >
        4) check if this is >>
        5) check if we need heredoc <<
        6) handle if this is a quote (do we need to verify 
                                    if there is a end)
        7) and of course add an end (TOKEN_END)
    while we verrify this we gonna check if the token is valid 
    check bottom ⬇️
*/
t_token tokenize_input(const char *input)
{
    int i;
    t_token *token;

    i = 0;
    while (input != '\0')
    {
        if (input[i] == '|')
            return (token[TOKEN_PIPE]);
        else if (input[i] == '<')

        else if (input[i] == '>')
        
        else if (input[i] == '>>')

        else if (input[i] == '<<') TOKEN_APPEND == 4

        else if (input[i] == '$VAR')

        else if (input[i] == TOKEN_END)


    }
}



/*
    here we gonna check if the token is ok with th rest of the str
    and if its good we gonna add it to the parsing and be ready to send it 
    to the struct arg how handle block by block the input
*/
int valid_token(t_token token)
{

}