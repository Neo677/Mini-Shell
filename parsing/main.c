/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:46 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/14 00:09:36 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_token *token;
	t_command *cmd_lst;
	t_buit_in exec;
	t_pipex pipex;
	
	token = NULL;
	init_var_builtin(&exec);
	init_var(&pipex);
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
			ft_printf("exit\n");
			break ; // ✅
		}
		
		add_history(exec.input);
		token = ft_parse_token(exec.input, &exec.env_cpy, &cmd_lst);
		if (!token)
			continue;
		else
		{
			check_heredoc(token, &pipex);
			check_file(token);
			child_process(&pipex, cmd_lst, &exec, env);
		}
		clear_file(pipex.filename_hd);
		free(exec.input);
	}
	free_tab(exec.tab);
	ft_free_token(token);
	rl_clear_history(); // (LINUX)
	// clear_history(); // (MACOS)
}


// a faire 
// fonction pour executer built in a la place de execve dans l'execution