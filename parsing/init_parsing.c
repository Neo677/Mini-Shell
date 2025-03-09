/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:26:55 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:27:06 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_free_process_line(t_buit_in *exec, t_pipex *pipex,
		t_command **cmd_lst, t_token *token)
{
	util_proc(exec, token, pipex);
	clear_history();
	ft_free_commande_lst(*cmd_lst);
	*cmd_lst = NULL;
	return (exec->exit_code_bh);
}

int	process_line(t_buit_in *exec, t_pipex *pipex, t_command **cmd_lst, int *lst)
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
	ft_mid_process(token, pipex, exec);
	if (*cmd_lst && (*cmd_lst)->arg)
	{
		process(pipex, *cmd_lst, exec, exec->env_dup);
		ctx.exit_status = exec->status;
		signal(SIGINT, signal_handler);
		if (exec->exit_bh == 1)
			return (ft_free_process_line(exec, pipex, cmd_lst, token));
		*lst = ctx.exit_status;
	}
	return (ft_end_process(token, exec, pipex), ft_free_commande_lst(*cmd_lst),
		*cmd_lst = NULL, 0);
}

void	init_cmd_ctx(t_parse_context *ctx, t_command **cmd_lst,
		t_command **current)
{
	*cmd_lst = NULL;
	*current = NULL;
	ctx->cmd_lst = cmd_lst;
	ctx->current = current;
}

void	ft_init_proc(t_parse_context ctx, int *lst, t_buit_in *exec)
{
	(void)ctx;
	ctx.current = NULL;
	ctx.env_cpy = &exec->env_cpy;
	ctx.last_token = NULL;
	ctx.exit_status = *lst;
}
