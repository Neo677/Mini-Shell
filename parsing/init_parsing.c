/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:26:55 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/11 10:47:48 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal = 0;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
		// rl_replace_line("", 0);
		// rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit (core dumped)\n");
	}
}

void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit (core dumped)\n");
	}
}

int	process_line(t_buit_in *exec, t_pipex *pipex, t_command **cmd_lst, int *lst)
{
	t_shell_context	ctx;
	t_token			*token;
	t_parse_context	pctx;

	g_signal = 0;
	ctx.exec = exec;
	ctx.pipex = pipex;
	ctx.cmd_lst = cmd_lst;
	ctx.lst = lst;
	pctx.cmd_lst = cmd_lst;
	ft_init_proc(pctx, lst, exec);
	if (read_input(exec) == -1)
		return (-1);
	if (g_signal != 0)
		*lst = g_signal;
	token = ft_parse_token(exec->input, &exec->env_cpy, cmd_lst, lst);
	if (!token)
		return (free(exec->input), ft_free_commande_lst(*cmd_lst), 0);
	if (is_minishell_call(&ctx))
		return (handle_minishell_cmd(&ctx, token));
	if (process_cmd(&ctx, token) == 1)
		return (exec->status);
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
