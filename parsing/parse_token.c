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

t_token *ft_parse_token(const char *input)
{
    t_token *token;
	
	token = NULL;
    if (!(input) || !(*input))
    {
        printf("[ERROR] Entrée vide\n");
        return (NULL);
    }
    ft_split_token(&token, input);
	if (!(input) || !(*input) || !token)
	{
		ft_printf("[ERROR] split token error render deteced\n");
		return (NULL);
	}
    return (token); // Retourne les tokens si tout est valide
}
