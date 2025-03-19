/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:49:36 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/18 14:49:39 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_exec_signals(void)
{
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
