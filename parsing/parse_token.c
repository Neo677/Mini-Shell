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
    Now that i finish to take an input / 
								split it / 
								check for every carac / 
								set in an enum struct 
    for reference it for the parser can regnoize the commande.
    Now i can add the arg, redirections, pipe in a struct cmd.
                        ⛓️⛓️⛓️
    1) Crée une commande vide 
    2) Gestions de lerreur d'alloc (leak safe)
    3) marque la commande qui contient un pipe
    4) arrete le parsing pour laisser un pipe gerer les commande suivante
    5) add une redicretions a la commande
    6) free
    7) add un arguments a la commande
    8) free
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
