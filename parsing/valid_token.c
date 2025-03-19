/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:46 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:48 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_valid_quotes(char **current, char quote_type)
{
	char	*start;
	size_t	len;
	char	*value;

	if (!current || !*current || !**current)
		return (ft_error_quote(), NULL);
	(*current)++;
	start = *current;
	len = 0;
	while (**current && **current != quote_type)
	{
		if (**current == '\\' && quote_type == '\"' && *(*current + 1) != '\0'
			&& (*(*current + 1) == quote_type || *(*current + 1) == '\\'))
			(*current)++;
		(*current)++;
		len++;
	}
	if (!**current)
		return (ft_error_quote(), NULL);
	value = ft_strndup(start, len);
	if (!value)
		return (ft_printf_fd(2, "minishell: memory allocation failed\n"), NULL);
	(*current)++;
	return (value);
}

int	ft_validay_quotes(t_token *token)
{
	char	*parsed_value;

	if (token->type == TOKEN_QUOTE || token->type == TOKEN_DBL_QUOTE)
	{
		parsed_value = ft_valid_quotes(&token->value, token->type);
		if (!parsed_value)
		{
			ft_printf_fd(STDERR_FILENO,
				"minishell: syntax error: unclosed quote\n");
			return (0);
		}
		free(parsed_value);
	}
	return (1);
}

int	ft_validate_pipes(t_token *token, t_parse_context *ctx)
{
	t_token	*prev;

	prev = NULL;
	(void)ctx;
	if (!token || token->type == TOKEN_PIPE)
		return (ctx->exit_status = 0, 0);
	while (token)
	{
		if (token->type == TOKEN_PIPE)
		{
			if (!prev || prev->type == TOKEN_PIPE)
				return (ctx->exit_status = 2, ft_printf_fd(2,
						"minishell: syntax error near unexpected token `|'\n"),
					0);
			if (!token->next)
				return (ctx->exit_status = 2, ft_printf_fd(2,
						"minishell: syntax error: pipe at the end\n"), 0);
		}
		prev = token;
		token = token->next;
	}
	return (1);
}

int	ft_valid_token(t_token *token, t_parse_context *ctx)
{
	t_token	*current;

	current = token;
	if (!ft_validate_pipes(current, ctx))
		return (0);
	if (!ft_valid_env_var(current))
		return (ctx->exit_status = 2, 0);
	while (current != NULL)
	{
		if (!ft_validay_quotes(current))
			return (ctx->exit_status = 2, 0);
		current = current->next;
	}
	return (1);
}
