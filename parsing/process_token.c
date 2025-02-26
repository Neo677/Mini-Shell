#include "minishell.h"

int	process_tokens(t_parse_context *ctx, int *last_exit_status)
{
	while (**ctx->input)
	{
		if (**ctx->input == ' ' || **ctx->input == '\t' || **ctx->input == ':')
			(*ctx->input)++;
		if (**ctx->input == '\'' || **ctx->input == '"')
		{
			if (ft_handle_quotes(ctx) == 0)
				return (error_cleanup(ctx, last_exit_status));
		}
		if (**ctx->input == '!')
			return (ctx->exit_status = 1, error_cleanup(ctx, last_exit_status));
		if (**ctx->input == '|' || **ctx->input == '>' || **ctx->input == '<')
		{
			if (!ft_handle_operators(ctx))
				return (error_cleanup(ctx, last_exit_status));
		}
		if (**ctx->input == '$')
			ft_handle_env_vars(ctx);
		else
		{
			if (!ft_handle_words(ctx))
				return (error_cleanup(ctx, last_exit_status));
		}
	}
	return (1);
}
