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

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	// t_parse_context ctx;
	t_token *token;
	t_buit_in exec;
	t_pipex pipex;
	
	token = NULL;
	init_var_builtin(&exec);
	init_var_pipex(&pipex);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	copy_env(env, &exec.env_cpy);
	modify_node_value(&exec.env_cpy, "_", "/usr/bin/env");
	// ft_intro();
	while (1)
	{
		// ctx.exit_status = 0;
		exec.input = readline("minishell> ");
		if (!exec.input)
		{
			ft_printf("exit\n");
			// ctx.exit_status = 258;
			break ; // ✅
		}
		add_history(exec.input);
		token = ft_parse_token(exec.input, &exec.env_cpy);
		// we can do if (!token = ft_parse_token(exec.input, &exec.env_cpy))
		if (!token)
		{
			free(exec.input);
			continue;
		}
		
		exec.tab = ft_token_to_tab(token);
		if ((ft_strcmp(exec.tab[0], "env") == 0) && ft_strlen(exec.tab[0]) == 3)
			ft_env(&exec.env_cpy);
		else if ((ft_strcmp(exec.tab[0], "pwd") == 0) && ft_strlen(exec.tab[0]) == 3)
			ft_pwd(&exec.env_cpy, exec.cd);
		else if ((ft_strcmp(exec.tab[0], "export") == 0) && ft_strlen(exec.tab[0]) == 6)
			ft_export(&exec.env_cpy, tab_export(exec.input));
		else if ((ft_strcmp(exec.tab[0], "unset") == 0) && ft_strlen(exec.tab[0]) == 5)
			ft_unset(&exec.env_cpy, exec.tab[1]);
		else if ((ft_strcmp(exec.tab[0], "echo") == 0) && ft_strlen(exec.tab[0]) == 4)
			ft_echo(exec.tab[1]);
		else if ((ft_strcmp(exec.tab[0], "exit") == 0) && ft_strlen(exec.tab[0]) == 4)
			return (ft_exit(&exec, exec.tab));
		else if ((ft_strcmp(exec.tab[0], "cd") == 0) && ft_strlen(exec.tab[0]) == 2)
			exec.cd = ft_cd(&exec.env_cpy, exec.tab[1]);
	
		free(exec.input);
		if (exec.tab != NULL)
		{
			free_tab(exec.tab);
			exec.tab = NULL;
		}
		ft_free_token(token);
		// clear_history(); // (MACOS)
	}
	rl_clear_history(); // (LINUX)
	// if (exec.tab != NULL)
	// {
	// 	free_tab(exec.tab);
	// 	exec.tab = NULL;
	// }
	return (0);
}

			// else if ((ft_strcmp(exec.tab[0], "echo") == 0) && ft_strlen(exec.tab[0]) == 4)
			// 	ft_echo(exec.tab);

// just apres avoir verifier que le fork a marche (recupe le dernie code exit)
// ctx->exit_status = WEXITSTATUS(status); // cruciale pour $?
