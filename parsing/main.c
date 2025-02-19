/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:46 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/19 21:24:56 by dpascal          ###   ########.fr       */
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
	int last_exit_status;
	
	last_exit_status = 0;
	token = NULL;
	init_var_builtin(&exec);
	init_var(&pipex);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
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
		token = ft_parse_token(exec.input, &exec.env_cpy, &cmd_lst, &last_exit_status);
		if (!token)
			continue;
		else
		{
			check_heredoc(token, &pipex);
			check_file(token);
			if (cmd_lst->arg)
			{
				child_process(&pipex, cmd_lst, &exec, env);
				signal(SIGINT, signal_handler);
				if (exec.exit_bh == 1)
				{
					free_all(&exec);
					ft_free_token(token);
					clear_file(pipex.filename_hd);
					rl_clear_history();
					return (exec.exit_code_bh);
				}
			}		
		}
		ft_free_token(token);
		ft_free_commande_lst(cmd_lst);
		free(exec.input);
		clear_file(pipex.filename_hd);
	}
	free_all(&exec);
	// ft_free_token(token);
	rl_clear_history(); // (LINUX)
	// clear_history(); // (MACOS)
}

// int main(int ac, char **av, char **env)
// {
// 	(void)ac;
// 	(void)av;
// 	t_token *token;
// 	t_command *cmd_lst;
// 	t_buit_in exec;
// 	t_pipex pipex;
// 	int last_exit_status;

// 	last_exit_status = 0;
// 	token = NULL;
// 	init_var_builtin(&exec);
// 	init_var(&pipex);
// 	signal(SIGINT, signal_handler);
// 	signal(SIGQUIT, signal_handler);
// 	copy_env(env, &exec.env_cpy);
// 	modify_node_value(&exec.env_cpy, "_", "/usr/bin/env");
// 	// ft_introw();
// 	while (1)
// 	{
// 		exec.input = readline("minishell> ");
// 		if (!exec.input)
// 		{
// 			ft_printf("exit\n");
// 			break ; // ✅
// 		}
// 		add_history(exec.input);
// 		token = ft_parse_token(exec.input, &exec.env_cpy, &cmd_lst, &last_exit_status);
// 		if (!token)
// 			continue;
// 		else
// 		{
// 			check_heredoc(token, &pipex);
// 			check_file(token);
// 			if (cmd_lst->arg)
// 				child_process(&pipex, cmd_lst, &exec, env);
// 		}
// 		ft_free_token(token);
// 		ft_free_commande_lst(cmd_lst);
// 		free(exec.input);
// 		clear_file(pipex.filename_hd);
// 	}
// 	free_env_list(exec.env_cpy);
// 	// free_tab(exec.tab);
// 	rl_clear_history(); // (LINUX)
// 	// rl_clear_history(); // (LINUX)
// 	// clear_history(); // (MACOS)
// }
