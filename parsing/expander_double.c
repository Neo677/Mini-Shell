#include "minishell.h"

static int	handle_dollar_dollar(t_parse_context *ctx, char *var_name)
{
	char	*var_value;

	free(var_name);
	var_value = ft_get_pid_str();
	if (!var_value)
		return (0);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: unbound variable\n");
		free(var_value);
		return (0);
	}
	free(var_value);
	return (1);
}

static int	handle_dollar_question(t_parse_context *ctx, char *var_name)
{
	char	*var_value;

	free(var_name);
	var_value = ft_itoa(ctx->exit_status);
	if (!var_value)
		return (0);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: unbound variable\n");
		free(var_value);
		return (0);
	}
	free(var_value);
	return (1);
}

static char	*handle_regular_env(t_parse_context *ctx, char *var_name)
{
	char	*var_value;

	var_value = print_node_by_key(ctx->env_cpy, var_name);
	if (!var_value)
		return (NULL);
	if (check_variable_backslash_n_parse(var_value) == 1)
		var_value = replace_with_space_parse(var_value);
	return (var_value);
}
int	ft_handle_env_vars_quote(t_parse_context *ctx)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_extract_env_var(ctx->input);
	if (!var_name)
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: error: invalid environment variable name\n");
		return (0);
	}
	if (ft_strcmp(var_name, "$$") == 0)
		return (handle_dollar_dollar(ctx, var_name));
	if (ft_strcmp(var_name, "$?") == 0)
		return (handle_dollar_question(ctx, var_name));
	var_value = handle_regular_env(ctx, var_name);
	if (!var_value)
		return (free(var_name), 0);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	free(var_name);
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
	{
		ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n");
		return (free(var_value), 0);
	}
	return (free(var_value), 1);
}
