/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:32:43 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:32:44 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_space(t_parse_context *ctx, char *quote_content)
{
	char	*new;

	new = ft_strjoin_v2(ctx->last_token->value, quote_content);
	if (!new)
		return (0);
	ctx->last_token->value = new;
	if (!ft_add_arguments(*ctx->current, quote_content))
		return (0);
	return (1);
}

static int	merge_quote_with_last(t_parse_context *ctx, char *quote_content)
{
	char	*new;

	new = ft_strjoin_v2(ctx->last_token->value, quote_content);
	if (!new)
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	ctx->last_token->value = new;
	if (!ft_add_arguments(*ctx->current, quote_content))
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	free(quote_content);
	return (1);
}

static int	add_quote_as_new_token(t_parse_context *ctx, char *quote_content)
{
	t_token	*token;

	token = ft_create_token(TOKEN_WORD, quote_content);
	ft_add_token(ctx->head, token);
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->cmd_lst, quote_content))
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	ctx->last_token = ft_last_token(*ctx->head);
	free(quote_content);
	return (1);
}

int	ft_handle_quotes(t_parse_context *ctx)
{
	char		*quote_content;
	const char	*input_ptr;
	char		prev_char;

	input_ptr = *ctx->input;
	quote_content = ft_handle_quote(ctx);
	if (!quote_content)
		return (0);
	if (input_ptr > ctx->input_exec)
		prev_char = *(input_ptr - 1);
	else
		prev_char = ' ';
	if (!ft_isspace(prev_char) && ctx->last_token && ctx->last_token->value)
		return (merge_quote_with_last(ctx, quote_content));
	else
		return (add_quote_as_new_token(ctx, quote_content));
}
