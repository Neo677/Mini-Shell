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
    Sépare l'input brut en morceaux interprétés comme des tokens :
    1) Ignore les espaces et tabulations.
    2) Gère les quotes (simples ou doubles).
    3) Gère les opérateurs (pipes, redirections).
    4) Gère les arguments et commandes.
    5) Arrête si une erreur de syntaxe est détectée.
*/


// void ft_split_token(t_token **head, const char *input)
// {
//     char *token_value;


//     if (!ft_check_syntax(input))
//         return;
//     while (*input)
//     {
//         if (*input == ' ' || *input == '\t') // Ignore les espaces et tabulations
//         {
//             input++;
//             continue;
//         }
//         else if (*input == '\'' || *input == '\"') // Gestion des quotes
//         {
//             token_value = ft_handle_quote(&input, *input);
//             if (!token_value)
//             {
//                 printf("[🚨 ERROR 🚨] Syntax error: unclosed quote\n");
//                 ft_free_token(*head);
//                 *head = NULL;
//                 return;
//             }
//             ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
//         }
//         else if (*input == '|' || *input == '>' || *input == '<') // Gestion des opérateurs
//         {
//             ft_handle_operator(head, &input);
//             if (*head == NULL) // Vérifie si une erreur a été détectée
//                 return;
//         }
//         else // Gestion des mots
//         {
//             token_value = ft_get_next_token(&input);
//             if (token_value && *token_value != '\0')
//                 ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
//         }
//     }
//     if (!ft_valid_token(*head)) // Vérification finale des tokens
//     {
//         ft_free_token(*head);
//         *head = NULL;
//     }
//     ft_print_tokens(*head);
// }

void ft_split_token(t_token **head, const char *input)
{
    char *token_value;
	char *file;
    t_command *cmd_lst;
    t_command *current;

    cmd_lst = NULL;
    current = NULL;
    if (!ft_check_syntax(input))
        return;
    while (*input)
    {
        if (*input == ' ' || *input == '\t') // Ignore les espaces et tabulations
        {
            input++;
            continue;
        }
        else if (*input == '\'' || *input == '\"') // Gestion des quotes
        {
            token_value = ft_handle_quote(&input, *input);
            if (!token_value)
            {
                ft_error_quote();
                ft_free_token(*head);
                *head = NULL;
				ft_free_commande_lst(cmd_lst);
                return;
            }
            ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
			
        }

        else if (*input == '|' || *input == '>' || *input == '<') 	// Gestion des opérateurs
        {
				// if a pipe is detected create evertything before is ONE command
			if (*(input - 1) == '|')
			{
				current = ft_create_command(&cmd_lst);
				if (!current)
				{
					ft_printf("[ERROR] failed to create command\n");
					ft_free_token(*head);
					*head = NULL;
					ft_free_commande_lst(cmd_lst);
					return;
				}
			}
			else if (*(input - 1) == '>' || *(input - 1) == '<')
			{
				file = ft_get_next_token(&input);
				if (!file)
				{
					ft_printf("[ERROR] Bad processing in the file redirections\n");
					ft_free_token(*head);
					*head = NULL;
					ft_free_commande_lst(cmd_lst);
					return;
				}
				if (!current)
					current = ft_create_command(&cmd_lst);
				if (!ft_add_redirections(current, ft_identify_token(token_value), file))
				{
					ft_printf("[ERROR] Issue encounter when the ...\n");
					ft_free_token(*head);
					*head = NULL;
					ft_free_commande_lst(cmd_lst);
					return;
				}
			}
        }
		// else if (ft_detect_env_var(&input) == 0)  // Gestion des variables environnements 
		// 	ft_extract_env_var(&input);

        else // Gestion des mots
        {

			token_value = ft_get_next_token(&input);
			if (token_value && *token_value != '\0')
				ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
        }
		input++;
    }
    if (ft_valid_token(*head) == 0) // Vérification finale des tokens
    {
		ft_printf("[ERROR] check the validity of the token\n");
        ft_free_token(*head);
        *head = NULL;
		ft_free_commande_lst(cmd_lst);
		return;
    }
    ft_print_tokens(*head);
}
