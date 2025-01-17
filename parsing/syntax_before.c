/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_before.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:20:12 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/13 13:20:14 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    the purpose of the syntax fonction :
    1) is to check the syntax global of the input before every single operations,
    2) She check if a big syntax error like quote not closed or anything else ...
    3) if an error is detected is unusless to keep going the lexing
*/

int ft_check_syntax(const char *input) {
    int quote = 0;

    while (*input) {
        // Ignorer les espaces
        if (*input == ' ') {
            input++;
            continue;
        }

        // Gestion des quotes
        if (*input == '\'' || *input == '\"') {
            if (quote == 0)
                quote = *input; // Quote ouverte
            else if (quote == *input)
                quote = 0; // Quote fermée
        }

        // Validation des pipes
        if (*input == '|') {
            input++;
            while (*input == ' ') input++; // Ignorer les espaces après le pipe
            if (*input == '|' || *input == '\0') {
                return (ft_printf("minishell: syntax error near unexpected token '|'\n"), 0);
            }
        }

        // Validation des redirections
        if (*input == '<' || *input == '>') {
            char current = *input;
            input++;
            while (*input == ' ') input++; // Ignorer les espaces après la redirection
            if (*input == '\0' || (*input == current && *(input + 1) == '\0')) {
                return (ft_printf("minishell: parse error near `\\n'\n"), 0);
            }
        }

        input++;
    }

    // Erreur si une quote reste ouverte
    if (quote != 0) {
        return (ft_printf("[🚨 ERROR 🚨] Syntax error: unclosed quote\n"), 0);
    }

    return (1);
}
