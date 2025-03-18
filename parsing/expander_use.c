/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_use.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:16:03 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/11 12:55:28 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_get_var_len(const char *input, size_t i)
{
	size_t	j;

	if (input[i + 1] == '$' || input[i + 1] == '?')
		return (2);
	j = i + 1;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	return (j - i);
}

char	*get_env_var_value(char *var, t_parse_context *ctx)
{
	char	*env_value;
	char	*var_value;
	char	*old;

	env_value = print_node_by_key(ctx->env_cpy, var + 1);
	if (env_value)
	{
		var_value = ft_strdup(env_value);
		if (!var_value)
			return (NULL);
		if (check_variable_backslash_n_parse(var_value) == 1)
		{
			old = var_value;
			var_value = replace_with_space_parse(var_value);
			free(old);
		}
	}
	else
		var_value = NULL;
	return (var_value);
}

char	*ft_extract_digit_var_quote(char *input)
{
	const char	*start;

	start = input;
	input++;
	return (ft_strndup(start, 1));
}

int	ft_get_this_digit(char *str)
{
	str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			return (1);
		str++;
	}
	return (0);
}

char	*get_var_value(const char *input, size_t var_len, t_parse_context *ctx)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_strndup(input, var_len);
	if (!var_name)
		return (NULL);
	if (ft_strcmp_dollar(var_name) == 0)
		return (var_name);
	if (ft_get_this_digit(var_name) == 1)
	{
		ft_extract_digit_var_quote(var_name);
		var_name += 2;
		return (var_name);
	}
	if (ft_strcmp(var_name, "$$") == 0)
		var_value = ft_get_pid_str();
	else if (ft_strcmp(var_name, "$?") == 0)
		var_value = ft_itoa(ctx->exit_status);
	else
		var_value = get_env_var_value(var_name, ctx);
	return (free(var_name), var_value);
}
