/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:46 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/19 23:01:53 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_shell_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	init_main(int ac, char **av, t_command **cmd_lst, int *lst)
{
	(void)ac;
	(void)av;
	*lst = 0;
	*cmd_lst = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_buit_in	exec;
	t_pipex		pipex;
	t_command	*cmd_lst;
	int			lst;
	int			ret;

	init_main(ac, av, &cmd_lst, &lst);
	init_var_builtin(&exec);
	init_var(&pipex);
	setup_shell_signals();
	ft_setup_env(&exec, env);
	ft_intro();
	while (1)
	{
		ret = process_line(&exec, &pipex, &cmd_lst, &lst);
		if (ret == -1 && (exec.exit_bh != 1 || exec.exit_bh != 2))
			break ;
		if (g_signal != 0 && ret != -1 && exec.exit_bh != 1)
			ret = g_signal;
		if (exec.exit_bh == 1 || exec.exit_bh == 2)
			return (ret);
	}
	if (g_signal != 0)
		exec.status = g_signal;
	return (free_all(&exec), rl_clear_history(), exec.status);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_buit_in	exec;
// 	t_pipex		pipex;
// 	t_command	*cmd_lst;
// 	int			lst;
// 	int			ret;

// 	(void)ac;
// 	(void)av;
// 	lst = 0;
// 	cmd_lst = NULL;
// 	init_var_builtin(&exec);
// 	init_var(&pipex);
// 	setup_shell_signals();
// 	ft_setup_env(&exec, env);
// 	ft_intro();
// 	while (1)
// 	{
// 		ret = process_line(&exec, &pipex, &cmd_lst, &lst);
// 		if (g_signal != 0)
// 			ret = g_signal;
// 		if (ret == -1)
// 			break ;
// 		else if (ret != 0 || exec.exit_bh == 1 || exec.exit_bh == 2)
// 			return (ret);
// 	}
// 	if (g_signal != 0)
// 		exec.status = g_signal;
// 	return (free_all(&exec), rl_clear_history(), exec.status);
// }
