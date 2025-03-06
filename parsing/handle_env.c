/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:16:22 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/06 13:40:39 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_replace_dol(char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	quest;

	i = 0;
	j = 0;
	quest = 0;
	while(var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '$')
		{
			while (var_value[j])
			{
				j++;
			}
			if (j == 1)
				quest++;
		}
		i++;
	}
	i += j -2;
	return (i + quest);
}

int	count_replace_quest(char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	quest;

	i = 0;
	j = 0;
	quest = 0;
	while(var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '?')
		{
			while (var_value[j])
			{
				j++;
			}
			if (j == 1)
				quest++;
		}
		i++;
	}
	i += j -2;
	return (i + quest);
}

char	*replace_quest(char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	k;
	int	quest;
	char *result;

	i = 0;
	j = 0;
	k = 0;
	quest = 0;
	result = malloc(sizeof(char) * count_replace_quest(var_value, var_name) + 1);
	if (!result)
		return (NULL);
	while(var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '?')
		{
			if (var_name[i + 2])
				i += 1;
			while (var_value[j])
				result[k++] = var_value[j++];
			if (j == 1)
				quest++;
		}
		if (i == 0)
		{
			result[k] = '\0';
			return (result);
		}
		result[k] = var_name[i + quest];
		i++;
		k++;
	}
	result[k] = '\0';
	return (result);
}

char	*replace_dol(char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	k;
	int	quest;
	char *result;

	i = 0;
	j = 0;
	k = 0;
	quest = 0;
	result = malloc(sizeof(char) * count_replace_dol(var_value, var_name) + 1);
	if (!result)
		return (NULL);
	while(var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '$')
		{
			if (var_name[i + 2])
				i += 2;
			while (var_value[j])
				result[k++] = var_value[j++];
			if (j == 1)
				quest++;
		}
		if (i == 0)
		{
			result[k] = '\0';
			return (result);
		}
		result[k] = var_name[i + quest];
		i++;
		k++;
	}
	result[k] = '\0';
	return (result);
}

int	ft_handle_doldol(t_parse_context *ctx, char *var_name)
{
	char	*var_value;

	var_value = ft_get_pid_str();
	if (!var_value)
		return (ft_printf_fd(STDERR_FILENO,
				"minishell: error: invalid environment variable name\n"),
			free(var_name), 0);
	char *tmp = var_value;
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

int	ft_handle_dolquest(t_parse_context *ctx, char *var_name)
{
	char	*test;
	char *var_value;

	test = ft_itoa(ctx->exit_status);
	if (!test)
		return (0);
	var_value = replace_quest(test, var_name);
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

int	ft_handle_dol(t_parse_context *ctx, char *var_name)
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

char	*extract_str(char *var_name)
{
	int	i;
	char	*new_str;

	i = 0;
	while (var_name[i] && var_name[i] != ' ')
	{
		i++;
	}
	new_str = malloc(sizeof(char) * i + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (var_name[i] && var_name[i] != ' ')
	{
		new_str[i] = var_name[i];
		i++;
	}
	new_str[i] = '\0';
	free(var_name);
	return (new_str);
}

int	ft_handle_env_vars(t_parse_context *ctx)
{
	char	*var_name;

	var_name = ft_extract_env_var(ctx->input);
	if (!var_name)
		return (free(var_name), 0);
	if (ft_strchr_comp_dol(var_name) == 0)
	{
		var_name = extract_str(var_name);
		if (!ft_handle_doldol(ctx, var_name))
			return (free(var_name), 0);
		return (2);
	}
	if (ft_strchr_comp_quest(var_name) == 0)
	{
		var_name = extract_str(var_name);
		if (!ft_handle_dolquest(ctx, var_name))
			return (free(var_name), 0);
		return (2);
	}
	else
	{
		if (!ft_handle_dol(ctx, var_name))
			return (free(var_name), 0);
		return (1);
	}
	return (free(var_name), 1);
}
