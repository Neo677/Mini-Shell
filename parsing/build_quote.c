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
	char	*pref;
	char	*qcont;
	char	*result;

	pref = ft_strdup_v2_quote(*ctx->input);
	if (!pref)
		return (NULL);
	qcont = ft_handle_quote(ctx);
	if (!qcont)
	{
		free(pref);
		return (NULL);
	}
	result = ft_strjoin(pref, qcont);
	free(pref);
	free(qcont);
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
