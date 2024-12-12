/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:18 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:19 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    separe input brut en morceaux de texte interpreter comme des tokens
    1) ignorer les white space
    2) handle quote (simple ou double)
    3) hande operator (pipe, redirections)
    4) handle word (arg, command)
*/

void	ft_split_token(t_token **head, const char *input)
{
	char			*token_value;
	t_token_arg		token_type;

	while (*input)
	{
		if (*input == ' ' || *input == '\t')
			input++;
		else if (*input == '\'' || *input == '\"')
		{
			token_value = ft_handle_quote(&input, *input);
			if (!token_value)
				error_exit("Erreur : quote non fermée.\n");
			ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
		}
		else if (*input == '|' || *input == '>' || *input == '<')
			ft_handle_operator(head, &input);
		// condtion pour gerer les variables 
		// environnements == eviter les '$$$$$'
		else if (*input == '$')
			ft_handle_env_var(head, &input);
		else
		{
			token_value = ft_get_next_token(&input); // ???
			if (token_value && *token_value != '\0')
			{
				token_type = TOKEN_WORD;
				ft_add_token(head, ft_create_token(token_type, token_value));
			}
		}
	}
	if (ft_valid_token(*head) == 0)
		printf("error detected\n");
}
