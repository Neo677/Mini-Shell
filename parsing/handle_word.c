/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:28:48 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/06 13:38:46 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_wave(t_parse_context *ctx, char *token_value)
{
	char	*var_value;

	if (!ctx || !token_value)
		return (0);
	var_value = print_node_by_key(ctx->env_cpy, "HOME");
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


static int	is_valid_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}


char	*ft_expand_variables(const char *str, t_parse_context *ctx)
{
	size_t	i;
	char	*result;
	char	*temp;
	char	*var_value;
	char	*var_name;
	char	c[2];

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			if (!str[i])
				break ;
			{
				size_t	start = i;
				while (str[i] && is_valid_var_char(str[i]))
					i++;
				var_name = ft_substr(str, start, i - start);
				if (!var_name)
					return (free(result), NULL);
				var_value = print_node_by_key(ctx->env_cpy, var_name);
				free(var_name);
				if (!var_value)
					var_value = "";
			}
			temp = result;
			result = ft_strjoin(result, var_value);
			free(temp);
			if (!result)
				return (NULL);
		}
		else
		{
			c[0] = str[i];
			c[1] = '\0';
			temp = result;
			result = ft_strjoin(result, c);
			free(temp);
			if (!result)
				return (NULL);
			i++;
		}
	}
	return (result);
}

int	ft_handle_words(t_parse_context *ctx)
{
	char	*token_value;
	t_token	*new;
	char	*expanded_value;

	token_value = ft_get_next_token(ctx->input);
	if (!token_value)
		return (0);
	if (ft_strcmp(token_value, "~") == 0)
	{
		if (!ft_handle_wave(ctx, token_value))
			return (free(token_value), 0);
	}
	if (ft_strchr(token_value, '$'))
	{
		expanded_value = ft_expand_variables(token_value, ctx);
		free(token_value);
		if (!expanded_value)
			return (0);
		token_value = expanded_value;
	}
	if (token_value && *token_value != '\0')
	{
		new = ft_create_token(TOKEN_WORD, token_value);
		if (!new)
			return (free(token_value), 0);
		if (!ft_handle_wds(ctx, token_value, new))
			return (free(token_value), ft_free_token(new), 0);
	}
	return (free(token_value), 1);
}
