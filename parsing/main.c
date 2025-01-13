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

void	ft_intro(void)
{
	ft_printf("\033[32m");
	ft_printf("\n  ███╗   ███╗██╗███╗   ██╗██╗\
	███████╗██╗  ██╗███████╗██╗     ██╗     \n");
	ft_printf("  ████╗ ████║██║████╗  ██║██║\
	██╔════╝██║  ██║██╔════╝██║     ██║\n");
	ft_printf("  ██╔████╔██║██║██╔██╗ ██║██║\
	███████╗███████║█████╗  ██║     ██║\n");
	ft_printf("  ██║╚██╔╝██║██║██║╚██╗██║██║\
	╚════██║██╔══██║██╔══╝  ██║     ██║\n");
	ft_printf("  ██║ ╚═╝ ██║██║██║ ╚████║██║\
	███████║██║  ██║███████╗███████╗███████╗\n");
	ft_printf("  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝\
	╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝\n");
	ft_printf("\033[0m\n");
    ft_printf("Bienvenue dans Minishell 🎉\n");
	ft_printf("Par Dpascal--Thobenel\n");
    ft_printf("Tapez 'exit' pour quitter.\n\n");
}

// int main(int ac, char **av, char **env)
// {
//     (void)ac;
//     (void)av;
//     (void)env;

// 	// ft_intro();
//     ft_start_minishell(); // Lancer Minishell
//     return (0);
// }

int main(int ac, char **av, char **env)
{
	char *input;
	t_command *cmd_lst;
	t_token *token;

	(void)ac;
	(void)av;
	(void)env; // the exec need it (tmp)
	cmd_lst = NULL;
	ft_intro();
	while (1)
	{
		input = readline("$> ");
		if (!input)
		{
			ft_printf("\n Bye bye ! 👋 \n");
			break ; // ✅
		}
			//return (ft_clean_up(&token, &input), ft_free_commande_lst(cmd_lst), 0);
		if (ft_handle_exit(input) == 0)
		{
			break;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
		token = ft_parse_token(input);
		if (!token)
		{
			ft_abort_parse(input);
			continue;
		}
		ft_print_tokens(token); // optionnal
		add_history(input);
		if (!ft_create_command_lst(token, &cmd_lst))
		{
			ft_free_commande_lst(cmd_lst);
			return (0);
		}
			// return (ft_abort_cmd(input, token), 0);
		
	}
	rl_clear_history();
}
