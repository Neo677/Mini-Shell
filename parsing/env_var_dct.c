/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_dct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:32 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/06 13:00:25 by dpascal          ###   ########.fr       */
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
	- Checks if the next character is a digit
		(Bash treats `$1` as a positional parameter).
	- Reads a single digit if it's a positional parameter.
	- Reads a standard identifier (alphanumeric + '_') otherwise.
	- Returns the literal "$" if no valid variable name is found.
	- Duplicates and returns the variable name.
*/

char	*ft_handle_special_case(const char **input)
{
	if ((*input)[1] == '$')
	{
		*input += 2;
		return (ft_strdup("$$"));
	}
	if ((*input)[1] == '?')
	{
		*input += 2;
		return (ft_strdup("$?"));
	}
	if ((*input)[1] == ' ')
		return (ft_strdup("$"));
	return (NULL);
}

char	*ft_extract_digit_var(const char **input)
{
	const char	*start;

	start = *input;
	(*input)++;
	return (ft_strndup(start, 1));
}

char	*ft_extract_alpha_var(const char **input)
{
	const char	*start;

	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	return (ft_strndup(start, *input - start));
}

char	*ft_extract_env_var(const char **input)
{
	char	*special;

	if (**input != '$')
		return (NULL);
	special = ft_handle_special_case(input);
	if (special)
		return (special);
	(*input)++;
	if (ft_isdigit(**input))
		return (ft_extract_digit_var(input));
	if (!ft_isalpha(**input) && **input != '_')
		return (ft_strdup("$"));
	if (**input != '"' || **input != '\'')
	{
		return (ft_extract_alpha_var(input));
	}
	return (NULL);
}
