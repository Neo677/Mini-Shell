#include "minishell.h"

void	init_cmd_ctx(t_parse_context *ctx, t_command **cmd_lst,
		t_command **current)
{
	ctx->cmd_lst = cmd_lst;
	ctx->current = current;
}

void	init_env_ctx(t_parse_context *ctx, t_token **head,
		const char *input, t_env **env_cpy)
{
	ctx->head = head;
	ctx->input = &input;
	ctx->input_exec = input;
	ctx->env_cpy = env_cpy;
	ctx->last_token = NULL;
}