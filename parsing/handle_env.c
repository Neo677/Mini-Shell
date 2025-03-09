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

int	count_replace_dol(char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	quest;

	i = 0;
	j = 0;
	quest = 0;
	while (var_name[i])
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
	i += j - 2;
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
	while (var_name[i])
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
	i += j - 2;
	return (i + quest);
}

char	*replace_quest(char *var_value, char *var_name)
{
	int		i;
	int		j;
	int		k;
	int		quest;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	quest = 0;
	result = malloc(sizeof(char) * count_replace_quest(var_value, var_name)
			+ 1);
	if (!result)
		return (NULL);
	while (var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '?')
		{
			if (var_name[i + 2])
				i += 2;
			while (var_value[j])
				result[k++] = var_value[j++];
			if (j == 1 && !var_name[i])
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
	int		i;
	int		j;
	int		k;
	int		quest;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	quest = 0;
	result = malloc(sizeof(char) * count_replace_dol(var_value, var_name) + 1);
	if (!result)
		return (NULL);
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

int ft_strcmp_dollar(char *varname)
{
    if (!varname)
        return 1;
    if (varname[0] == '$' && (varname[1] == '\0' || varname[1] == ' '))
        return 0;
    return 1;
}

int	ft_handle_alones(t_parse_context *ctx, char *var_name)
{
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_name));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_name))
		return (ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"),
			free(var_name), 0);
	return (1);
}


int	ft_handle_env_vars(t_parse_context *ctx)
{
	char	*var_name;

	var_name = ft_extract_env_var(ctx->input);
	if (!var_name)
		return (free(var_name), 0);
	if (ft_strcmp_dollar(var_name) == 0)
	{
		if (!ft_handle_alones(ctx, var_name))
			return (free(var_name), 0);
		return (2);
	}
	if (ft_strchr_comp_dol(var_name) == 0)
	{
		var_name = extract_str(var_name);
		if (!ft_handle_doldoles(ctx, var_name))
			return (free(var_name), 0);;
		return (1);
	}
	if (ft_strchr_comp_quest(var_name) == 0)
	{
		var_name = extract_str(var_name);
		if (!ft_handle_dolquestes(ctx, var_name))
			return (free(var_name), 0);
		return (1);
	}
	if (!ft_handle_doles(ctx, var_name))
		return (free(var_name), 0);
	return (1);
}
