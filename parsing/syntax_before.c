/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_before.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:20:12 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/17 12:34:36 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_set_syntax_quote(const char *input, int *quote)
{
	if (*quote == 0)
		*quote = *input;
	else if (*quote == *input)
		*quote = 0;
}

int	ft_set_syntax_pipe(const char *input)
{
	if (*input == '|' || *input == '\0')
	{
		ft_printf("before minishell: syntax error near unexpected token '|'\n");
		return (0);
	}
	return (1);
}

int	ft_set_syntax_redir(const char *input)
{
    input++;
    while (*input == ' ')
        input++;
    if (*input == '\0' || *input == '|')
    {
        ft_printf("before minishell: parse error near `\\n'\n");
        return (0);
    }
    return (1);
}

int ft_check_syntax(const char *input)
{
    int quote;
	
	quote = 0;
    while (*input)
    {
        if (*input == '\'' || *input == '\"')
            ft_set_syntax_quote(input, &quote);
        if (quote == 0)
        {
            if (*input == '|')
            {
				input++;
                if (ft_set_syntax_pipe(input) == 0)
					return (0);
            }
            if (*input == '<' || *input == '>')
				if (ft_set_syntax_redir(input) == 0)
					return (0);
        }
        input++;
    }
    if (quote != 0)
        return (ft_printf("befor minishell: syntax error: unclosed quote\n"), 0);
    return (1);
}

// int	ft_check_syntax(const char *input)
// {
// 	char	current;
// 	int		quote;

// 	quote = 0;
// 	while (*input)
// 	{
// 		if (*input == ' ')
// 			input++;
// 		else if (*input == '\'' || *input == '\"')
// 			ft_set_syntax_quote(input, &quote);
// 		else if (*input == '|')
// 		{
// 			if (ft_set_syntax_pipe(input) == 0)
// 				return (0);
// 			input++;
// 		}
// 		else if (*input == '<' || *input == '>')
// 		{
// 			current = *input;
// 			if (ft_set_syntax_redir(current, input) == 0)
// 				return (0);
// 			input++;
// 				return (0);
// 		}
// 		input++;
// 	}
// 	if (quote != 0)
// 		return (ft_printf("[🚨 ERROR 🚨] Syntax error: unclosed quote\n"), 0);
// 	return (1);
// }

/*
    the purpose of the syntax fonction :
    1) is to check the syntax global of the input before every single operations,
    2) She check if a big syntax error like quote not closed or anything else ...
    3) if an error is detected is unusless to keep going the lexing

   -Ignorer les espaces
   -Gestion des quotes
   -Quote ouverte
   -Quote fermée
   -Validation des pipes
   -Ignorer les espaces après le pipe
   -Validation des redirections
   -Ignorer les espaces après la redirection
   -Erreur si une quote reste ouverte
*/
