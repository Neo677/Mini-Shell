/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:16:22 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/06 14:29:21 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_result_dol(char *result, char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	k;
	int	quest;

	i = 0;
	j = 0;
	k = 0;
	quest = 0;
	while (var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '$')
		{
			if (var_name[i + 2])
				i += 2;
			while (var_value[j])
				result[k++] = var_value[j++];
			if (j == 1 && !var_name[i])
				quest++;
		}
		if (i == 0)
			return (result[k] = '\0', 0);
		result[k++] = var_name[i++ + quest];
	}
	return (result[j] = '\0', 1);
}

char	*replace_dol(char *var_value, char *var_name)
{
	char	*result;

	result = malloc(sizeof(char) * count_replace_dol(var_value, var_name) + 1);
	if (!result)
		return (NULL);
	fill_result_dol(result, var_value, var_name);
	return (result);
}

int	ft_strcmp_dollar(char *varname)
{
	if (!varname)
		return (1);
	if (varname[0] == '$' && (varname[1] == '\0' || varname[1] == ' '))
		return (0);
	return (1);
}

int	ft_handle_alones(t_parse_context *ctx, char *var_name)
{
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_name));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_name))
		return (ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"),
			free(var_name), 0);
	ctx->exit_status = 127;
	free(var_name);
	return (1);
}

int	ft_handle_env_vars(t_parse_context *ctx, int *last_exit_status)
{
	char	*var_name;
	int		res;

	var_name = ft_extract_env_var(ctx->input);
	if (!var_name)
		return (0);
	if (ft_strcmp_dollar(var_name) == 0)
	{
		res = ft_handle_alones(ctx, var_name);
		return (res);
	}
	if (ft_strchr_comp_dol(var_name) == 0)
	{
		res = ft_handle_doldoles(ctx, extract_str(var_name));
		return (res);
	}
	if (ft_strchr_comp_quest(var_name) == 0)
	{
		res = ft_handle_dolquestes(ctx, extract_str(var_name));
		return (res);
	}
	if (!ft_handle_doles(ctx, var_name))
		return (free(var_name), 0);
	*last_exit_status = ctx->exit_status;
	return (1);
}
