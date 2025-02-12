/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:46 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/12 07:39:47 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// char	*join_input(char **tab)
// {
// 	char	*str;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	str = ft_strdup("");
// 	if (!str)
// 		return (NULL);
// 	while (tab[i])
// 	{
// 		printf("tab[%d] = %s\n", i, tab[i]);
// 		tmp = str;
// 		str = ft_strjoin(str, tab[i]);
// 		free(tmp);
// 		if (!str)
// 			return (NULL);
// 		i++;
// 	}
// 	return (str);
// }

char	*test_input(t_token *token)
{
	char	*str;
	t_token	*current;
	int	onoff;
	
	onoff = 1;
	str = NULL;
	current = token;
	while (current)
	{
		str = ft_strjoin(str, current->value);
		if (onoff == 1 && current->next)
		{
			str = ft_strjoin(str, " ");
			onoff = 0;
		}
		current = current->next;
	}
	return (str);
	
}

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
			// printf("token = %s\n", test_input(token));
			// printf("token == %s\n", token->value);
			exec.tab = ft_token_to_tab(token);
			// printf("TEST  === %s\n", join_input(exec.tab));
			// printf ("tab[0] = %s\n", exec.tab[0]);
			// printf ("tab[1] = %s\n", exec.tab[1]);
			// printf ("tab[2] = %s\n", exec.tab[2]);
			// printf ("tab[3] = %s\n", exec.tab[3]);
			// printf ("tab[4] = %s\n", exec.tab[4]);
			if ((ft_strcmp2(exec.tab[0], "env") == 0) && ft_strlen(exec.tab[0]) == 3)
				ft_env(&exec.env_cpy);
			else if ((ft_strcmp2(exec.tab[0], "pwd") == 0) && ft_strlen(exec.tab[0]) == 3)
				ft_pwd(&exec.env_cpy, exec.cd);
			else if ((ft_strcmp2(exec.tab[0], "export") == 0) && ft_strlen(exec.tab[0]) == 6)
				ft_export(&exec.env_cpy, tab_export(test_input(token)));
			else if ((ft_strcmp2(exec.tab[0], "unset") == 0) && ft_strlen(exec.tab[0]) == 5)
				ft_unset(&exec.env_cpy, exec.tab[1]);
			else if ((ft_strcmp2(exec.tab[0], "echo") == 0) && ft_strlen(exec.tab[0]) == 4)
				ft_echo(exec.tab[1]);
			else if ((ft_strcmp2(exec.tab[0], "exit") == 0) && ft_strlen(exec.tab[0]) == 4)
				return(ft_exit(&exec, exec.tab));
			else if ((ft_strcmp2(exec.tab[0], "cd") == 0) && ft_strlen(exec.tab[0]) == 2)
				exec.cd = ft_cd(&exec.env_cpy, exec.tab[1]);
			else if ((ft_strcmp2(exec.tab[0], "./minishell") == 0) && ft_strlen(exec.tab[0]) == 11)
				main(ac, av, exec.tab);
			else
				child_process(&pipex, cmd_lst, env);
			// ft_printf_fd(127,"minishell: Command not found\n");
		}
		clear_file(pipex.filename_hd);
		free(exec.input);
	}
	free_tab(exec.tab);
	ft_free_token(token);
	rl_clear_history(); // (LINUX)
	// clear_history(); // (MACOS)
}
