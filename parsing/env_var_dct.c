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
    11/12/2024
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

int	ft_detect_env_var(const char *str)
{
	if (*str == '$' && *(str + 1) && ft_isalpha(*(str + 1)))
		return (1);
	return (0);
}

char	*ft_extract_env_var(const char **input)
{
	const char	*start;
	char		*env_var;

	(*input)++;
	start = *input;
	while (**input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	if (start == *input)
	{
		ft_error_env("invalid env variable :(");
		return (NULL);
	}
	env_var = ft_strndup(start, *input - start);
	return (env_var);
}
