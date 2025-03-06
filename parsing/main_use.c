/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_use.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:27:38 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 08:27:41 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_setup_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_setup_env(t_buit_in *exec, char **env)
{
	exec->env_dup = env;
	copy_env(env, &exec->env_cpy);
	modify_node_value(&exec->env_cpy, "_", "/usr/bin/env");
}

void	util_proc(t_buit_in *exec, t_token *token, t_pipex *pipex)
{
	free_all(exec);
	ft_free_token(token);
	clear_file(pipex->filename_hd);
}

void	ft_end_process(t_token *token, t_buit_in *exec, t_pipex *pipex)
{
	ft_free_token(token);
	free(exec->input);
	clear_file(pipex->filename_hd);
}

void	ft_mid_process(t_token *token, t_pipex *pipex, t_buit_in *exec)
{
	check_heredoc(token, pipex);
	check_file(exec, token);
}
