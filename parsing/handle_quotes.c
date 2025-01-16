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

static char *ft_handle_single_quote(const char **input)
{
    const char *start;
    char *content;
    size_t i;

    i = 0;
    if (**input != '\'')
        return (NULL);
    
    start = ++(*input);  // Skip opening quote
    while ((*input)[i] && (*input)[i] != '\'')
        i++;
    
    if ((*input)[i] != '\'')  // Check if quote is closed
        return (NULL);
    
    content = ft_strndup(start, i);
    if (!content)
        return (NULL);
    
    (*input) += i + 1;  // Move past closing quote
    return (content);
}

static char *ft_handle_double_quote(const char **input)
{
    const char *start;
    char *content;
    size_t i;

    i = 0;
    if (**input != '\"')
    {
        return (NULL);
    }
    start = ++(*input);  // Skip opening quote
    while ((*input)[i] && (*input)[i] != '\"')
    {
        if ((*input)[i] == '\\' && ((*input)[i + 1] == '\"' || (*input)[i + 1] == '\\' || (*input)[i + 1] == '$'))
        {
            i += 2;  // Skip escaped character
        }
        else if ((*input)[i] == '$')
        {
            i++;
        }
        else
        {
            i++;
        }
    }
    if ((*input)[i] != '\"')  // Check if quote is closed
    {
        return (NULL);
    }
    
    content = ft_strndup(start, i);
    if (!content)
        return (NULL);
    
    // Process escape sequences and variables
    // result = process_double_quote_content(content);
    // free(content);
    (*input) += i + 1;  // Move past closing quote
    return (content);
}

char *ft_handle_quote(const char **input)
{
    char *content;

    if (**input == '\'')
    {
        content = ft_handle_single_quote(input);
    }
        
    else if (**input == '\"')
    {
        content = ft_handle_double_quote(input);
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


