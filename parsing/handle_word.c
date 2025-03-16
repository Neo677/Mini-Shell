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

static char	*append_char_to_result(char *result, char c)
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

static char	*handle_dollar(const char *str, size_t *i, t_parse_context *ctx,
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
			if (!str[i++])
				break ;
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

static int	process_token(char **token_value, t_parse_context *ctx)
{
	char	*expanded_value;

	if (ft_strcmp(*token_value, "~") == 0)
	{
		if (!ft_handle_wave(ctx, *token_value))
		{
			free(*token_value);
			return (0);
		}
	}
	if (ft_strchr(*token_value, '$'))
	{
		expanded_value = ft_expand_variables(*token_value, ctx);
		free(*token_value);
		if (!expanded_value)
			return (0);
		*token_value = expanded_value;
	}
	return (1);
}

int	ft_handle_words(t_parse_context *ctx)
{
	char *token_value;
	t_token *new;

	token_value = ft_get_next_token(ctx->input);
	if (!token_value)
		return (0);
	if (!process_token(&token_value, ctx))
		return (0);
	if (token_value && *token_value != '\0')
	{
		new = ft_create_token(TOKEN_WORD, token_value);
		if (!new)
		{
			free(token_value);
			return (0);
		}
		if (!ft_handle_wds(ctx, token_value, new))
		{
			free(token_value);
			ft_free_token(new);
			return (0);
		}
	}
	free(token_value);
	return (1);
}
