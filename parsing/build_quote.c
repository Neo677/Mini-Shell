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

char	*build_quote_content(t_parse_context *ctx)
{
	char	*result;
	char	*temp;
	char	*pref;
	char	*joined;

	if (!ctx || !ctx->input || !(*ctx->input))
		return (NULL);
	result = ft_strdup_v2_quote(*ctx->input);
	if (!result)
		return (NULL);
	temp = ft_handle_quote(ctx);
	if (!temp)
	{
		free(result);
		return (NULL);
	}
	joined = ft_strjoin(result, temp);
	free(result);
	free(temp);
	if (!joined)
	{
		ft_printf_fd(2, "minishell: memory allocation failed\n");
		return (NULL);
	}
	result = joined;
	while (**ctx->input == '\"' || **ctx->input == '\'')
	{
		pref = ft_strdup_v2_quote(*ctx->input);
		if (!pref)
		{
			free(result);
			return (NULL);
		}
		temp = ft_handle_quote(ctx);
		if (!temp)
		{
			free(pref);
			free(result);
			return (NULL);
		}
		joined = ft_strjoin(result, pref);
		free(pref);
		if (!joined)
		{
			free(temp);
			free(result);
			ft_printf_fd(2, "minishell: memory allocation failed\n");
			return (NULL);
		}
		pref = ft_strjoin(joined, temp);
		free(temp);
		free(joined);
		if (!pref)
		{
			free(result);
			ft_printf_fd(2, "minishell: memory allocation failed\n");
			return (NULL);
		}
		result = pref;
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
