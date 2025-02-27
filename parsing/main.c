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

void	ft_setup_signal(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_setup_env(t_buit_in *exec, char **env)
{
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

void	ft_mid_process(t_token *token, t_pipex *pipex)
{
	check_heredoc(token, pipex);
	check_file(token);
}

void	ft_init_proc(t_parse_context ctx, int *lst, t_buit_in *exec)
{
	ctx.current = NULL;
	ctx.env_cpy = &exec->env_cpy;
	ctx.last_token = NULL;
	ctx.exit_status = *lst;
}

int	process_line(t_buit_in *exec, t_pipex *pipex, t_command **cmd_lst,
		int *lst, char **env)
{
	t_token			*token;
	t_parse_context	ctx;

	ctx.cmd_lst = cmd_lst;
	ft_init_proc(ctx, lst, exec);
	exec->input = readline("minishell> ");
	if (!exec->input)
		return (ft_printf("exit\n"), -1);
	add_history(exec->input);
	token = ft_parse_token(exec->input, &exec->env_cpy, cmd_lst, lst);
	if (!token)
		return (free(exec->input), 0);
	ft_mid_process(token, pipex);
	if (*cmd_lst && (*cmd_lst)->arg)
	{
		ctx.exit_status = child_process(pipex, *cmd_lst, exec, env);
		signal(SIGINT, signal_handler);
		if (exec->exit_bh == 1)
			return (util_proc(exec, token, pipex), clear_history(),
				exec->exit_code_bh);
		*lst = ctx.exit_status;
	}
	return (ft_end_process(token, exec, pipex), 0);
}

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
		ret = process_line(&exec, &pipex, &cmd_lst, &lst, env);
		if (ret == -1)
			break ;
		else if (ret != 0)
			return (ret);
	}
	free_all(&exec);
	clear_history();
	return (0);
}
