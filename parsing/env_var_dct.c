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

    Extracts the environment variable name from the input string.
    - Skips the '$' character.
    - Checks if the next character is a digit (Bash treats `$1` as a positional parameter).
    - Reads a single digit if it's a positional parameter.
    - Reads a standard identifier (alphanumeric + '_') otherwise.
    - Returns the literal "$" if no valid variable name is found.
    - Duplicates and returns the variable name.
*/

char *ft_detec_var(const char **input)
{
    char *var_name;

    var_name = ft_strndup(*input, 1);
    (*input)++;
    return (var_name);
}

int     ft_detec_digit(int is_digit_param, const char **input)
{
        if (ft_isdigit(**input))
            is_digit_param = 1;
        return (is_digit_param);
}

char *ft_extract_env_var(const char **input)
{
    const char  *start;
    char        *var_name;
    int          is_digit_param;

    is_digit_param = 0;
    if (**input == '$')
        (*input)++;
    if (**input == '\0' || **input == ' ' || **input == '\t' || **input == '$')
        return (ft_strdup_v2("$"));
    if (**input == '?' || **input == '$')
        return (ft_detec_var(input));
    is_digit_param = ft_detec_digit(is_digit_param, input);
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
        return (ft_strdup_v2("$"));
    var_name = ft_strndup(start, (*input - start));
    if (!var_name)
        return (NULL);
    return (var_name);
}
