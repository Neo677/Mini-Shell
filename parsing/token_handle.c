/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:12:07 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/11 20:37:03 by dpascal          ###   ########.fr       */
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

int	ft_is_redirection(t_token *token)
{
	if (token->type == TOKEN_IN || token->type == TOKEN_OUT
		|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	handle_pipe(t_token **head, const char **input)
{
	t_token	*new_token;

	if (*(*input + 1) == '|')
	{
		ft_error_pipe("||");
		*input += 2;
		ft_free_token(*head);
		*head = NULL;
		return (0);
	}
	(*input)++;
	new_token = ft_create_token(TOKEN_PIPE, "|");
	if (!new_token)
	{
		ft_free_token(new_token);
		*head = NULL;
		return (0);
	}
	ft_add_token(head, new_token);
	return (1);
}

int	handle_redirection(t_token **head, const char **input)
{
	char	operateur[3];
	t_token	*new_token;

	operateur[0] = **input;
	operateur[1] = '\0';
	operateur[2] = '\0';
	(*input)++;
	if (**input == operateur[0])
	{
		operateur[1] = **input;
		(*input)++;
		operateur[2] = '\0';
	}
	if (!**input || **input == '|' || **input == '<' || **input == '>')
	{
		ft_error_redirections(operateur);
		ft_free_token(*head);
		return (*head = NULL, (*input)++, 0);
	}
	new_token = ft_create_token(ft_identify_token(operateur), operateur);
	if (!new_token)
		return (ft_free_token(new_token), *head = NULL, 0);
	ft_add_token(head, new_token);
	return (1);
}

int	ft_handle_operator(t_token **head, const char **input)
{
	if (**input == '|')
		return (handle_pipe(head, input));
	else if (**input == '>' || **input == '<')
		return (handle_redirection(head, input));
	return (1);
}

// int ft_handle_operator(t_token **head, const char **input)
// {
//     char operateur[3];
//     t_token *new_token;

//     if (**input == '|') 				// Gestion des pipes
//     {
//         if (*(*input + 1) == '|')		// Double pipe (||)
//         {
//             ft_error_pipe("||");
//             (*input) += 2;
//             ft_free_token(*head);		// Libère les tokens déjà créés
//             *head = NULL;				// Réinitialise la liste
//             return (0);						// Arrête immédiatement
//         }
//         (*input)++;
//         new_token = ft_create_token(TOKEN_PIPE, "|");
//         if (!new_token)
//         {
//             ft_free_token(new_token);
//             *head = NULL;
//             return (0);
//         }
//         ft_add_token(head, new_token);
//     }
//     else if (**input == '>' || **input == '<')
//     {
//         operateur[0] = **input;
//         operateur[1] = 0;
//         operateur[2] = 0;
//         (*input)++;
//         if (**input == operateur[0])
//         {
//             operateur[1] = **input;
//             (*input)++;
//             operateur[2] = '\0';
//         }
//         if (!**input || **input == '|' || **input == '<' || **input == '>')
//         {
//             ft_error_redirections(operateur);
//             ft_free_token(*head);
//             *head = NULL;
//             (*input)++;
//             return (0);
//         }
//         new_token = ft_create_token(ft_identify_token(operateur), operateur);
//         if (!new_token)
//         {
//             ft_free_token(new_token);
//             *head = NULL;
//             return (0);
//         }
//         ft_add_token(head, new_token);
//     }
//     return (1);
// }
