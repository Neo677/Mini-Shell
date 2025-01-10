/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_dct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:32 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:24:33 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
    11/12/2024 :
    Now that i almost fix the pipe issue i can attack 
    the env variables : 
    i need to check in my parsing if i find a '$'
    once i get it ive got to 
    1) check if the expression $VAR_NAME is correct
    2) identifie the syntax error 
        a. $ alone
        b. $VAR$OTHER incorrect
    3) associated the TOKEN_ENV_VAR in the enum
        and allocate is value brut for the parseur
    4) assure myself that the env var is use in a 
        good context
*/

// unusless

int ft_detect_env_var(const char *str)
{
    if (str && *str == '$' && *(str + 1) != '\0')
        return (1);
    return (0);
}

/*
    Extracts the environment variable name from the input string.
    - Skips the '$' character.
    - Checks if the next character is a digit (Bash treats `$1` as a positional parameter).
    - Reads a single digit if it's a positional parameter.
    - Reads a standard identifier (alphanumeric + '_') otherwise.
    - Returns the literal "$" if no valid variable name is found.
    - Duplicates and returns the variable name.
*/

char *ft_extract_env_var(const char **input)
{
    const char  *start;
    char        *var_name;
    int          is_digit_param;

    (*input)++;
    if (ft_isdigit(**input))
        is_digit_param = 1;
    else
        is_digit_param = 0;
    start = *input;
    if (is_digit_param)
    {
        if (ft_isdigit(**input))
            (*input)++;
    }
    else
    {
        while (**input && (ft_isalnum(**input) || **input == '_'))
            (*input)++;
    }
    if (start == *input)
        return (ft_strdup("$"));
    var_name = ft_strndup(start, (*input - start));
    return (var_name);
}