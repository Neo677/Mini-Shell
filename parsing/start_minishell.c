/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:20:01 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/13 13:20:03 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_abort(char *input)
{
	ft_printf("\n Bye bye ! 👋 \n");
	free(input);
	return;
}

void	ft_abort_parse(char *input)
{
	printf("[ERROR] Invalid syntax\n");
	free(input);
	return;
}

void	ft_abort_cmd(char *input, t_token *token)
{
	ft_printf("[ERROR] start error creating cmd\n");
	if (input)
		free(input);
	if (token)
		free(token);
	ft_clean_up(&token, &input);
	return;
}

// void	ft_start_minishell(void)
// {
// 	char		*input;
// 	t_command	*cmd_lst;
// 	t_token		*token;

// 	cmd_lst = NULL;
// 	while (1)
// 	{
// 		input = readline("$> "); // ✅
// 		if (!input) // Gestion de Ctrl-D ou erreur de readline
// 		{
// 			ft_printf("\n Bye bye ! 👋 \n");
// 			break ; // ✅
// 		}
// 		if (ft_handle_exit(input) == 0)
// 			break; // ✅
// 		if (input[0] == '\0')
// 		{
// 			free(input);
// 			continue ; // ✅
// 		}
// 		token = ft_parse_token(input, );
// 		ft_print_tokens(token); // ✅
// 		add_history(input); // ✅
// 		if (!ft_create_command_lst(token, &cmd_lst))
// 		{
// 			ft_printf("[ERROR] start error creating cmd\n");
// 			ft_clean_up(&token, &input); // ✅
// 			return;
// 		}
// 		// exec ...
// 		ft_clean_up(&token, &input);
// 	}
// }
