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
	return (free(quote_content), 1);
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
	return (free(quote_content), 1);
}

char	*ft_strdup_v2_quote(const char *src)
{
	char	*dst;
	int		i;

	i = 0;
	while (src[i] && src[i] == ' ')
		i++;
	dst = malloc(sizeof(char) * (i + 1));
	if (dst == NULL)
		return (NULL);
	i = 0;
	while (src[i] && src[i] == ' ')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_handle_quotes(t_parse_context *ctx)
{
	char	*quote_content;
	char	*prefix;
	char	*combined;
	char	*rest;
	char	*merged;

	prefix = ft_strdup_v2_quote(*ctx->input);
	quote_content = ft_handle_quote(ctx);
	if (!quote_content)
		return (free(prefix), 0);
	combined = ft_strjoin(prefix, quote_content);
	free(prefix);
	if (!combined)
		return (free(quote_content), 0);
	if (*ctx->input && !ft_isspace(**ctx->input))
	{
		rest = ft_get_next_token(ctx->input);
		merged = ft_strjoin(combined, rest);
		if (!merged)
			return (free(rest), free(combined), 0);
		return (free(rest), free(combined), merge_quote_with_last(ctx, merged));
	}
	else
		return (free(quote_content), free(combined), add_quote_as_new_token(ctx,
				combined));
}
