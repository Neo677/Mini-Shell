/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:38:44 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/16 08:38:45 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char *ft_handle_single_quote(const char **input) {
    const char *start;
    char *content;
    size_t i = 0;

    if (**input != '\'') {
        return (NULL);
    }

    start = ++(*input); // Sauter la quote ouvrante

    // Parcourir jusqu'à la quote fermante
    while ((*input)[i] && (*input)[i] != '\'') {
        i++;
    }

    if ((*input)[i] != '\'') { // Erreur si quote fermante absente
        ft_printf("[ERROR] Unclosed single quote\n");
        return (NULL);
    }

    // Copier le contenu entre les quotes
    content = ft_strndup(start, i);
    if (!content) {
        ft_printf("[ERROR] Memory allocation failed in ft_handle_single_quote\n");
        return (NULL);
    }

    (*input) += i + 1; // Sauter la quote fermante
    return (content);
}

static char *ft_handle_double_quote(const char **input, t_token **head, t_command **cmd_lst, t_command **current) {
    const char *start;
    char *content = NULL;
    char *temp_content;
    size_t i = 0;

    if (**input != '\"') {
        return (NULL); // Double quote non trouvée
    }

    (*input)++; // Sauter la quote ouvrante
    start = *input;

    while (**input) {
        // Parcourir jusqu'à la prochaine quote fermante ou caractère spécial
        while ((*input)[i] && (*input)[i] != '\"') {
            if ((*input)[i] == '\\' && ((*input)[i + 1] == '\"' || (*input)[i + 1] == '\\' || (*input)[i + 1] == '$')) {
                i += 2; // Sauter les caractères échappés
            } else if ((*input)[i] == '$') {
                // Gestion des variables d'environnement
                *input += i; // Avancer jusqu'au `$`
                ft_handle_env_vars(input, head, cmd_lst, current);
                i = 0; // Réinitialiser après le traitement
                start = *input; // Réinitialiser le début
            } else {
                i++;
            }
        }

        // Vérifier si une quote fermante est trouvée
        if ((*input)[i] == '\"') {
            temp_content = ft_strndup(start, i);
            if (!temp_content) {
                ft_printf("[ERROR] Memory allocation failed in ft_handle_double_quote\n");
                return (NULL);
            }

            // Concaténer les contenus si nécessaire
            if (content) {
                char *new_content = ft_strjoin(content, temp_content);
                free(content);
                free(temp_content);
                if (!new_content) {
                    ft_printf("[ERROR] Memory allocation failed during concatenation\n");
                    return (NULL);
                }
                content = new_content;
            } else {
                content = temp_content;
            }

            (*input) += i + 1; // Sauter la quote fermante

            // Vérifier si une autre quote suit immédiatement
            if (**input == '\"') {
                (*input)++; // Sauter l'ouverture de la prochaine quote
                start = *input;
                continue; // Reprendre l'analyse
            }
            break; // Fin de l'analyse des quotes
        } else {
            ft_printf("[ERROR] Unclosed double quote\n");
            return (NULL);
        }
    }

    return (content);
}


char *ft_handle_quote(const char **input, t_token **head, t_command **cmd_lst, t_command **current) {
    char *content = NULL;

    if (**input == '\'') {
        content = ft_handle_single_quote(input);
    } else if (**input == '\"') {
        content = ft_handle_double_quote(input, head, cmd_lst, current);
    }

    if (!content) {
        ft_printf("[DEBUG] Error while handling quote content\n");
        return (NULL);
    }

    return (content);
}

// char *ft_handle_quote(const char **input, char quote_type)
// {
//     const char *start;
//     char *content;
//     char single_quote_char;
//     char double_quote_char;

//     t_token token_instance;
//     t_token *token = &token_instance;
//     // token->single_quote = false;
//     // token->double_quote = false;
//     size_t i;
//     char start_quote;

//     ft_printf("1.0\n");

//     i = 0;
//     ft_printf("1.1\n");
//     single_quote_char = '\'';
//     double_quote_char = '\"';
//     ft_printf("1.2\n");
//     start_quote = **(input);
//     ft_printf("1.3\n");
//     start = ++(*input);
//     ft_printf("1debut = %s\n", double_quote_char);
//     // ft_printf("2debut = %s\n", double_quote_char);
//     ft_printf("3debut = %s\n", start_quote);
//     ft_printf("4debut = %s\n", start);

//     if (start_quote == single_quote_char)
//         token->single_quote = true;
//     else if (start_quote == double_quote_char)
//         token->double_quote = true;
//     ft_printf("1\n");
    
//     while ((*input)[i] && (*input)[i] != quote_type)
//     {
//         ft_printf("2\n");
//         if (quote_type == '\'' && token->single_quote == true)
//         {
//             ft_printf("3\n");
//             content = ft_handle_single_quote(input);
//         }
            
//         else if (quote_type == double_quote_char && token->double_quote == true)
//         {
//             ft_printf("4\n");
//             content = ft_handle_double_quote(input);
//         }
//         ft_printf("5\n");
        
//         i++;
//     }
//     ft_printf("6\n");
//     if ((*input)[i] != quote_type)
//     {
//         ft_printf("7\n");
//         return (NULL);
//     }
//     ft_printf("8\n");
//     if ((*input)[i] != quote_type)
//     {
//         return (printf("[DEBUG] quote non closed\n"), NULL);
//     }
//     ft_printf("9\n");

//     // content = ft_strndup(start, i);
//     // if (!content)
//     //     return (free(content), NULL);
//     // (*input) += i + 1; // Increment input pointer to skip the closing quote
//     return (content);
// }


