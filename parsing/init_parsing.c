#include "minishell.h"

void	init_cmd_ctx(t_parse_context *ctx, t_command **cmd_lst,
							 t_command **current)
{
	*cmd_lst = NULL;
	*current = NULL;
	ctx->cmd_lst = cmd_lst;
	ctx->current = current;
}
