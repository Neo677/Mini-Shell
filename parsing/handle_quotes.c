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

// static char *ft_handle_single_quote(const char **input) 
// {
//     const char *start;
//     char *content;
//     size_t i;

//     i = 0;
//     if (**input != '\'')
//         return (NULL);
//     start = ++(*input);
//     while ((*input)[i] && (*input)[i] != '\'')
//         i++;
//     if ((*input)[i] != '\'')
//     {
//         ft_printf_fd(STDERR_FILENO, "minishell: syntax error: unclosed single quote\n");
//         return (NULL); // return 258 pour la fonctions appelante
//     }
//     content = ft_strndup(start, i);
//     if (!content)
//     {
//         ft_printf_fd(STDERR_FILENO, "minishell: error: memory allocation failed in ft_handle_single_quote\n");
//         return (NULL); // probleme interne
//     }
//     printf("content  %s\n", content);
//     (*input) += i + 1;
//     return (content);
// }

// /*
//     - Double quote non trouvée
//     - Sauter la quote ouvrante
//     - Parcourir jusqu'à la prochaine quote fermante ou caractère spécial
//     - Sauter les caractères échappés
//     - Gestion des variables d'environnement
//     -  Avancer jusqu'au `$`
//         - Réinitialiser après le traitement
//         - Réinitialiser le début
//     - Vérifier si une quote fermante est trouvée
//     - Concaténer les contenus si nécessaire
//     - Sauter la quote fermante
//     - Vérifier si une autre quote suit immédiatement
//     - Sauter l'ouverture de la prochaine quote
//     - Reprendre l'analyse
//     - Fin de l'analyse des quotes
// */

t_quote init_quote(void)
{
    return ((t_quote){0, 0, 0});
}

static int ft_handle_single_quote(const char **input, t_quote *state)
{
    state->in_single = !state->in_single;
    (*input)++;
    return (1);
}

static int ft_handle_double_quote(const char **input, t_quote *state)
{
    state->in_double = !state->in_double;
    (*input)++;
    return (1);
}

char *ft_handle_quote(const char **input, t_quote *state)
{
    char *content;

    content = NULL;
    if (**input == '\'' && !state->in_double)
    {
        if (!ft_handle_single_quote(input, state))
            return (NULL);
    }
    if (**input == '"' && !state->in_single)
    {
        if (!ft_handle_double_quote(input, state))
            return (NULL);
    }
    else
        content = ft_extract_quotent(input, state);
    return (content);
}

// char *ft_handle_quote(const char **input, char quote_type)
// {
//     const char *start;
//     char *content;
//     char single_quote_char;
//     char double_quote_char;

//     t_token token_instance;char *ft_handle_quote(const char **input, t_token **head, t_command **cmd_lst, t_command **current, t_buit_in *env_cpy);

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


