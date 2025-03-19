/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:26:55 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/19 18:36:49 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

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
	if (process_cmd(exec, &ctx, token) == 1)
		return (exec->status);
	return (ft_end_process(token, exec, pipex), ft_free_commande_lst(*cmd_lst),
		*cmd_lst = NULL, 0);
}
