/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:32:51 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:32:53 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_handle_doldol(t_parse_context *ctx, char *var_name)
{
	char	*var_value;

	free(var_name);
	var_value = ft_get_pid_str();
	if (!var_value)
		return (ft_printf_fd(STDERR_FILENO,
				"minishell: error: invalid environment variable name\n"), 0);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
		return (ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"),
			free(var_value), 0);
	free(var_value);
	return (1);
}

static int	ft_handle_dolquest(t_parse_context *ctx, char *var_name)
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
		return (ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"),
			free(var_value), 0);
	free(var_value);
	return (1);
}

static int	ft_handle_dol(t_parse_context *ctx, char *var_name)
{
	char	*var_value;

	var_value = print_node_by_key(ctx->env_cpy, var_name);
	if (!var_value)
		return (free(var_value), 0);
	if (check_variable_backslash_n_parse(var_value) == 1)
		var_value = replace_with_space_parse(var_value);
	if (!var_value)
		return (0);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	free(var_name);
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
		return (ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"),
			free(var_value), 0);
	return (1);
}

int	ft_handle_env_vars_quote(t_parse_context *ctx)
{
	char	*var_name;

	var_name = ft_extract_env_var(ctx->input);
	if (!var_name)
		return (free(var_name), 0);
	if (ft_strcmp(var_name, "$$") == 0)
	{
		if (!ft_handle_doldol(ctx, var_name))
			return (0);
	}
	if (ft_strcmp(var_name, "$?") == 0)
	{
		if (!ft_handle_dolquest(ctx, var_name))
			return (0);
	}
	else
	{
		if (!ft_handle_dol(ctx, var_name))
			return (0);
	}
	return (1);
}
