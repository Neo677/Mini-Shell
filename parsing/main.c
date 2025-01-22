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
	(void)ac;
	(void)av;
	(void)env;

	// int cd;
	char *input;

	t_token *token;

	// t_env *env_cpy;

	// char **tab;
	
	// env_cpy = NULL;
	// copy_env(env, &env_cpy);
    // modify_node_value(&env_cpy, "_", "/usr/bin/env");

	// ft_intro();
	ft_set
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_printf("\n Bye bye ! 👋 \n");
			break ; // ✅
		}
		// if (ft_handle_exit(input) == 0)
		// 	break;
		// if (input[0] == '\0')
		// {
		// 	ft_main_free(cmd_lst, cmd_lst->redirections, token);
		// }
			
		token = ft_parse_token(input);
		add_history(input);
	
	    // tab = ft_split_built(input, ' ');
        // if (ft_strcmp_exec(tab[0], "env") == 0)
        //     ft_env(&env_cpy);
        // else if (ft_strcmp_exec(tab[0], "pwd") == 0)
        //     ft_pwd(&env_cpy, &cd);
        // else if (ft_strcmp_exec(tab[0], "export") == 0)
        //     ft_export(&env_cpy, tab[1]);
        // else if (ft_strcmp_exec(tab[0], "unset") == 0)
        //     ft_unset(&env_cpy, tab[1]);
        // else if (ft_strcmp_exec(tab[0], "echo") == 0)
        //     ft_echo(tab);
        // else if (ft_strcmp_exec(tab[0], "exit") == 0)
        //     return(ft_exit(&env_cpy, tab));
        // else if (ft_strcmp_exec(tab[0], "./minishell") == 0)
        //     main(ac, av, tab);
        // else if (ft_strcmp_exec(tab[0], "cd") == 0)
            // cd = ft_cd(&env_cpy, tab[1]);
	}
	clear_history(); // (MACOS)
	ft_free_token(token);
	//	rl_clear_history(); // (LINUX)
}
