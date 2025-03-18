/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:26:12 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/11 14:26:13 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_quote_content(t_parse_context *ctx)
{
	char	*result;
	char	*temp;
	char	*joined;

	result = ft_strdup_v2_quote(*ctx->input);
	if (!result)
		return (NULL);
	temp = ft_handle_quote(ctx);
	if (!temp)
		return (free(result), NULL);
	joined = ft_strjoin(result, temp);
	free(result);
	free(temp);
	if (!joined)
		return (NULL);
	return (joined);
}

char	*extract_quote_segment(t_parse_context *ctx, const char *current_result)
{
	char	*pref;
	char	*temp;
	char	*joined;
	char	*new_result;

	pref = ft_strdup_v2_quote(*ctx->input);
	if (!pref)
		return (NULL);
	temp = ft_handle_quote(ctx);
	if (!temp)
		return (free(pref), NULL);
	joined = ft_strjoin((char *)current_result, pref);
	free(pref);
	if (!joined)
		return (free(temp), NULL);
	new_result = ft_strjoin(joined, temp);
	free(temp);
	free(joined);
	if (!new_result)
		return (NULL);
	return (new_result);
}

char	*build_quote_content(t_parse_context *ctx)
{
	char	*result;
	char	*temp_result;

	if (!ctx || !ctx->input || !(*ctx->input))
		return (NULL);
	result = init_quote_content(ctx);
	if (!result)
		return (NULL);
	while (**ctx->input == '\"' || **ctx->input == '\'')
	{
		temp_result = extract_quote_segment(ctx, result);
		free(result);
		if (!temp_result)
			return (NULL);
		result = temp_result;
	}
	return (result);
}

int	merge_with_next(t_parse_context *ctx, char *quote)
{
	char	*merged;

	merged = ft_get_next_token(ctx->input);
	free(quote);
	if (!merged)
		return (0);
	return (merge_quote_with_last(ctx, merged));
}

int	handle_quote_with_next(t_parse_context *ctx, char *quote)
{
	int		ret;
	char	*dup;

	dup = ft_strdup(quote);
	if (!dup)
	{
		free(quote);
		return (0);
	}
	ret = add_quote_as_new_token(ctx, quote);
	if (!ret)
	{
		free(dup);
		return (0);
	}
	return (merge_with_next(ctx, dup));
}
