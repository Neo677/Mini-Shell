/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:32:43 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/20 12:15:10 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_space(t_parse_context *ctx, char *quote_content)
{
	char	*new;
	char	*old;

	old = ctx->last_token->value;
	new = ft_strjoin_v2(old, quote_content);
	if (!new)
		return (0);
	free(old);
	ctx->last_token->value = new;
	if (!ft_add_arguments(*ctx->current, quote_content))
		return (0);
	return (1);
}

int	merge_quote_with_last(t_parse_context *ctx, char *quote_content)
{
	char	*new;
	char	*old;

	old = ctx->last_token->value;
	new = ft_strjoin_v2(old, quote_content);
	if (!new)
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	free(old);
	ctx->last_token->value = new;
	if (!ft_add_arguments(*ctx->current, quote_content))
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	return (free(quote_content), 1);
}

int	add_quote_as_new_token(t_parse_context *ctx, char *quote_content)
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
	const char	*qstart;
	char		pr;
	char		next;
	char		*quote;
	int			ret;

	pr = ' ';
	next = ' ';
	qstart = *ctx->input;
	quote = build_quote_content(ctx);
	if (!quote)
		return (0);
	if (qstart > ctx->input_exec)
		pr = *(qstart - 1);
	if (**ctx->input)
		next = **ctx->input;
	ret = 0;
	if (!ft_isspace(pr) && !ft_isspace(next) && (pr != '<' && pr != '>'))
		ret = merge_with_next(ctx, quote);
	else if (!ft_isspace(pr) && ft_isspace(next) && (pr != '<' && pr != '>'))
		ret = merge_quote_with_last(ctx, quote);
	else
		ret = add_quote_as_new_token(ctx, quote);
	return (ret);
}
