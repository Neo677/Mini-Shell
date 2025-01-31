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

char **ft_token_to_tab(t_token *token)
{
	int count;
	int i;
	t_token *tmp;
	char **tab;

	count = 0;
	tmp = token;
	while (tmp)
	{
		count++;
		tmp = tmp->next;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	tmp = token;
	i = 0;
	while (tmp)
	{
		tab[i] = ft_strdup_v2(tmp->value);
		if (!tab[i])
		{
			while (i > 0)
				free(tab[i--]);
			free(tab);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	tab[i] = NULL;
	return (tab);
}



int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_buit_in exec;
	t_token *token;
	t_pipex pipex;
	
	token = NULL;
	init_var_builtin(&exec);
	init_var(&pipex);

	// ft_set_signal_handler();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);


	copy_env(env, &exec.env_cpy);

	modify_node_value(&exec.env_cpy, "_", "/usr/bin/env");

	// ft_intro();

	while (1)
	{

		exec.input = readline("minishell> ");

		if (!exec.input)
		{
			ft_printf("CTRL-D\n");
			// need to content a free fonction
			// also return te right code
			break ; // ✅
		}

		token = ft_parse_token(exec.input, &exec.env_cpy);
		if (!token)
		{
			ft_printf_fd(STDERR_FILENO, "syntax error near unexpected token `newline'\n");
			continue;
		}
		// recupe $cmd_lst

		exec.tab = ft_token_to_tab(token);
		// exec.tab = ft_split_built(exec.input, ' ');

		if (ft_strcmp2(exec.tab[0], "env") == 0)
			ft_env(&exec.env_cpy);
		else if (ft_strcmp2(exec.tab[0], "pwd") == 0)
		{
			ft_pwd(&exec.env_cpy, exec.cd);
		}
		else if (ft_strcmp2(exec.tab[0], "export") == 0)
			ft_export(&exec.env_cpy, exec.tab[1]);
		else if (ft_strcmp2(exec.tab[0], "unset") == 0)
			ft_unset(&exec.env_cpy, exec.tab[1]);
		else if (ft_strcmp2(exec.tab[0], "echo") == 0)
			ft_echo(exec.tab);
		else if (ft_strcmp2(exec.tab[0], "exit") == 0)
			return(ft_exit(&exec, exec.tab));
					/*
						[DEBUG] arg = [exit]
					----------------------------------
					*** stack smashing detected ***: terminated
					Aborted (core dumped)
					*/
		else if (ft_strcmp2(exec.tab[0], "cd") == 0)
			exec.cd = ft_cd(&exec.env_cpy, exec.tab[1]);
		else if (ft_strcmp2(exec.tab[0], "./minishell") == 0)
			main(ac, av, exec.tab);
		if (exec.input)
			add_history(exec.input);
		free(exec.input);
	}
	
	// free(exec.tab);
	free_tab(exec.tab);
	ft_free_token(token);
	// clear_history(); // (MACOS)
	rl_clear_history(); // (LINUX)
}
