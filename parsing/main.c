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
	i = 0;
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
	while (tmp)
	{
		tab[i] = ft_strdup(tmp->value);
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

// void	ft_handle_command(char **tab, t_env env_cpy, int cd)
// {
// 	tab = ft_token_to_tab(token);
// 	if (ft_strcmp_exec(tab[0], "env") == 0)
// 		ft_env(&env_cpy);
// 	else if (ft_strcmp_exec(tab[0], "pwd") == 0)
// 		ft_pwd(&env_cpy, &cd);
// 	else if (ft_strcmp_exec(tab[0], "export") == 0)
// 		ft_export(&env_cpy, tab[1]);
// 	else if (ft_strcmp_exec(tab[0], "unset") == 0)
// 		ft_unset(&env_cpy, tab[1]);
// 	else if (ft_strcmp_exec(tab[0], "echo") == 0)
// 		ft_echo(tab);
// 	else if (ft_strcmp_exec(tab[0], "exit") == 0)
// 		return(ft_exit(&env_cpy, tab));
// 	else if (ft_strcmp_exec(tab[0], "./minishell") == 0)
// 		main(ac, av, tab);
// 	else if (ft_strcmp_exec(tab[0], "cd") == 0)
// 		cd = ft_cd(&env_cpy, tab[1]);
// }

int main(int ac, char **av, char **env)
{
	int cd;
	char *input;
	t_token *token;
	t_env *env_cpy;
	char **tab;

	(void)ac;
	(void)av;
	
	token = NULL;
	tab = NULL;
	env_cpy = NULL;

	copy_env(env, &env_cpy);
    modify_node_value(&env_cpy, "_", "/usr/bin/env");
	ft_set_signal_handler();
	// ft_intro();
	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			ft_printf("exit\n");
			break ; // ✅
		}
		if (input[0] == '\0')
		{
			free(input);
			continue;
		}
			
		token = ft_parse_token(input, env_cpy);

		if (token)
		{
			tab = ft_token_to_tab(token);
			if (ft_strcmp_exec(tab[0], "env") == 0)
				ft_env(&env_cpy);
			else if (ft_strcmp_exec(tab[0], "pwd") == 0)
				ft_pwd(&env_cpy, &cd);
			else if (ft_strcmp_exec(tab[0], "export") == 0)
				ft_export(&env_cpy, tab[1]);
			else if (ft_strcmp_exec(tab[0], "unset") == 0)
				ft_unset(&env_cpy, tab[1]);
			else if (ft_strcmp_exec(tab[0], "echo") == 0)
				ft_echo(tab);
			else if (ft_strcmp_exec(tab[0], "exit") == 0)
				return(ft_exit(&env_cpy, tab));
			else if (ft_strcmp_exec(tab[0], "./minishell") == 0)
				main(ac, av, tab);
			else if (ft_strcmp_exec(tab[0], "cd") == 0)
				cd = ft_cd(&env_cpy, tab[1]);
			// if (!ft_handle_command(tab, &env_cpy, &cd))
			// 	ft_printf("minishell: %s: command not found\n", tab[0]);
			add_history(input);
		}
	}
	clear_history(); // (MACOS)
	free_tab(tab);
	ft_free_token(token);
	//	rl_clear_history(); // (LINUX)
}
