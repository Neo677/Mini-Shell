/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_use.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:26:26 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/11 14:26:27 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_doldoles(t_parse_context *ctx, char *var_name)
{
	char	*var_value;
	char	*tmp;

	var_value = ft_get_pid_str();
	if (!var_value)
		return (ft_printf_fd(STDERR_FILENO,
				"minishell: error: invalid environment variable name\n"),
			free(var_name), 0);
	tmp = var_value;
	var_value = replace_dol(var_value, var_name);
	free(tmp);
	free(var_name);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
		return (ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"),
			free(var_value), 0);
	free(var_value);
	return (1);
}

int	ft_handle_dolquestes(t_parse_context *ctx, char *var_name)
{
	char	*val;
	char	*var_value;

	val = ft_itoa(ctx->exit_status);
	if (!val)
		return (0);
	var_value = replace_quest(val, var_name);
	free(var_name);
	free(val);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
		return (ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"),
			free(var_value), 0);
	free(var_value);
	return (1);
}

int	ft_handle_doles(t_parse_context *ctx, char *var_name)
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

int	ft_strchr_comp_quest(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i] && var_name[i] != ' ')
	{
		if (var_name[i] == '$' && var_name[i + 1] == '?')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strchr_comp_dol(char *var_name)
{
	int	i;

	i = 0;
	while (var_name[i] && var_name[i] != ' ')
	{
		if (var_name[i] == '$' && var_name[i + 1] == '$')
			return (0);
		i++;
	}
	return (1);
}
