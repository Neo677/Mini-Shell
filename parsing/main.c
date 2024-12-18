/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:46 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:24:48 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_intro(void)
{
    const char *intro[] = {
        "#########################################",
        "#         🎉 WELCOME TO MINISHELL 🎉     #",
        "#  (Build)Dpascal AND Thobenel(parsing) #",
        "#        LEXER PART BY thobenel         #",
        "#########################################",
        "Enter command below for tokenize that shit 🧑‍🍳",
        "type 'exit' to quit this shell, dude",
        NULL
    };
	ft_printf("%s", intro);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	t_token	*token;

	(void)ac;
	(void)av;
	(void)env;
	//ft_intro();
	while (1)
	{
		input = readline("$> "); // posibilite de leak (readline)
		if (!input)
		{
			error_exit("Bye bye ! 👋 \n");
			break ;
		}
		ft_printf("[INFO]  Tokenizing input: '%s'\n", input);
		ft_handle_exit(input);
		token = ft_parse_token(input);
		ft_print_tokens(token);
		ft_clean_up(&token, &input);
	}
	return (0);
}
