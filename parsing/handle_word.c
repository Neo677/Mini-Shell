#include "minishell.h"

int	ft_handle_wave(t_parse_context *ctx, char *token_value)
{
	char	*var_value;

	if (!ctx || !token_value)
		return (0);
	var_value = print_node_by_key(ctx->env_cpy, "HOME");
	free(token_value);
	if (!var_value)
		return (0);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	if (!ctx->head)
		return (free(var_value), 0);
	if (!ctx->current || !ctx->cmd_lst)
		return (free(var_value), 0);
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!*ctx->current || !ft_add_arguments(*ctx->current, var_value))
		return (ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"),
			free(var_value), 0);
	return (1);
}

int	ft_handle_wds(t_parse_context *ctx, char *token_value, t_token *new)
{
	if (!ctx || !token_value || !new)
		return (0);
	ft_add_token(ctx->head, new);
	if (!ctx->head)
		return (ft_free_token(new), 0);
	ctx->last_token = new;
	if (!ctx->current || !ctx->cmd_lst)
		return (0);
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!*ctx->current || !ft_add_arguments(*ctx->current, token_value))
		return (free(token_value), 0);
	return (1);
}

int	ft_handle_words(t_parse_context *ctx)
{
	char	*token_value;
	t_token	*new;

	if (!ctx || !ctx->input)
		return (0);
	token_value = ft_get_next_token(ctx->input);
	if (!token_value)
		return (0);
	if (ft_strcmp(token_value, "~") == 0)
	{
		if (!ft_handle_wave(ctx, token_value))
			return (free(token_value), 0);
	}
	if (token_value && *token_value != '\0')
	{
		new = ft_create_token(TOKEN_WORD, token_value);
		if (!new)
			return (0);
		if (!ft_handle_wds(ctx, token_value, new))
			return (0);
	}
	return (1);
}
