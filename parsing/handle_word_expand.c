/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:31:15 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/17 11:31:20 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	*append_char_to_result(char *result, char c)
{
	char	buf[2];
	char	*tmp;

	buf[0] = c;
	buf[1] = '\0';
	tmp = result;
	result = ft_strjoin(result, buf);
	free(tmp);
	return (result);
}

char	*handle_dollar(const char *str, size_t *i, t_parse_context *ctx,
		char *result)
{
	size_t	start;
	char	*var_name;
	char	*var_value;
	char	*tmp;

	start = *i;
	while (str[*i] && is_valid_var_char(str[*i]))
		(*i)++;
	var_name = ft_substr(str, start, *i - start);
	if (!var_name)
	{
		free(result);
		return (NULL);
	}
	var_value = print_node_by_key(ctx->env_cpy, var_name);
	free(var_name);
	if (!var_value)
		var_value = "";
	tmp = result;
	result = ft_strjoin(result, var_value);
	free(tmp);
	return (result);
}

char	*ft_expand_variables(const char *str, t_parse_context *ctx)
{
	size_t	i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			result = handle_dollar(str, &i, ctx, result);
			if (!result)
				return (NULL);
		}
		else
		{
			result = append_char_to_result(result, str[i]);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}
