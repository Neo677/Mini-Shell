/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:31:01 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/20 09:43:40 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_free_process_line(t_buit_in *exec, t_pipex *pipex, t_command **cmd_lst,
		t_token *token)
{
	util_proc(exec, token, pipex);
	rl_clear_history();
	ft_free_commande_lst(*cmd_lst);
	*cmd_lst = NULL;
	return (exec->status);
}

int	read_input(t_buit_in *exec)
{
	exec->input = readline("minishell> ");
	if (!exec->input)
	{
		ft_printf("exit\n");
		return (-1);
	}
	if (ft_strcmp(exec->input, "") != 0)
		add_history(exec->input);
	return (0);
}

int	is_minishell_call(t_shell_context *ctx)
{
	if (!ctx || !ctx->exec || !ctx->cmd_lst || !(*ctx->cmd_lst))
		return (0);
	if (ctx->exec->input && (*ctx->cmd_lst)->arg)
	{
		if (ft_strcmp_shell(ctx->exec->input, "./minishell") == 0)
			return (1);
		if ((*ctx->cmd_lst)->arg[0] && ft_strcmp((*ctx->cmd_lst)->arg[0],
				"./minishell") == 0 && !((*ctx->cmd_lst)->arg[1]))
			return (1);
	}
	return (0);
}

int	handle_minishell_cmd(t_shell_context *ctx, t_token *token)
{
	t_parse_context	pctx;

	run_shell(ctx->exec);
	pctx.exit_status = ctx->exec->status;
	*(ctx->lst) = pctx.exit_status;
	free_tab(ctx->exec->env);
	ft_end_process(token, ctx->exec, ctx->pipex);
	ft_free_commande_lst(*(ctx->cmd_lst));
	return (0);
}

int	process_cmd(t_buit_in *exec, t_shell_context *ctx, t_token *token)
{
	t_parse_context	pctx;

	check_heredoc(exec, token, ctx->pipex);
	*(ctx->lst) = exec->status;
	if (*(ctx->cmd_lst) && (*(ctx->cmd_lst))->arg && exec->hd == 0)
	{
		process(ctx->pipex, *(ctx->cmd_lst), ctx->exec, ctx->exec->env_cpy);
		free_tab(ctx->exec->env);
		pctx.exit_status = ctx->exec->status;
		signal(SIGINT, signal_handler);
		if (ctx->exec->exit_bh == 1 || ctx->exec->exit_bh == 2)
		{
			if (ctx->exec->exit_bh == 2)
				exec->status = *(ctx->lst);
			ft_free_process_line(ctx->exec, ctx->pipex, ctx->cmd_lst, token);
			return (1);
		}
		*(ctx->lst) = pctx.exit_status;
	}
	if ((*ctx->cmd_lst))
	{
		if ((*ctx->cmd_lst)->redirections && !((*ctx->cmd_lst)->arg))
			change_dir(ctx->exec, *ctx->cmd_lst, ctx->pipex);
	}
	return (0);
}
