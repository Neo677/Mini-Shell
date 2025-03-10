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

int	main(int ac, char **av, char **env)
{
	t_buit_in	exec;
	t_pipex		pipex;
	t_command	*cmd_lst;
	int			lst;
	int			ret;

	(void)ac;
	(void)av;
	lst = 0;
	cmd_lst = NULL;
	init_var_builtin(&exec);
	init_var(&pipex);
	ft_setup_signal();
	ft_setup_env(&exec, env);
	while (1)
	{
		ret = process_line(&exec, &pipex, &cmd_lst, &lst);
		if (ret == -1)
			break ;
		else if (ret != 0 || exec.exit_bh == 1)
			return (ret);
	}
	return (free_all(&exec), rl_clear_history(), 0);
}
