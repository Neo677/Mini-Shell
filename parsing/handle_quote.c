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

	if (!ctx || !ctx->last_token || !quote_content)
		return (0);
	old = ctx->last_token->value;
	if (!old)
		return (0);
	new = ft_strjoin_v2(old, quote_content);
	if (!new)
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	free(old);
	ctx->last_token->value = new;
	if (!ft_add_arguments(*ctx->current, new))
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

size_t	count_remaining(const char **strs)
{
	size_t	re_len;

	re_len = 0;
	while ((*strs)[re_len] && !ft_isspace((*strs)[re_len])
		&& (*strs)[re_len] != '\'' && (*strs)[re_len] != '\"'
		&& (*strs)[re_len] != '|' && (*strs)[re_len] != '<'
		&& (*strs)[re_len] != '>' && (*strs)[re_len] != '$')
		re_len++;
	return (re_len);
}

char	*ft_strjoin_remaining(const char *str, const char **strs)
{
	char	*result;
	size_t	len;
	size_t	re_len;
	size_t	i;

	if (!str || !strs || !*strs)
		return (NULL);
	len = ft_strlen_v2(str);
	re_len = count_remaining(strs);
	result = malloc(sizeof(char) * (len + re_len + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, str, len + 1);
	i = 0;
	while (i < re_len)
	{
		result[len + i] = (*strs)[i];
		i++;
	}
	result[len + i] = '\0';
	*strs += re_len;
	return (result);
}

static int	h_quote_merge(t_parse_context *ctx, char **final, char *temp,
		char *quote_content)
{
	char	*new;

	new = ft_strjoin_remaining(temp, ctx->input);
	free(temp);
	if (!new)
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	*final = new;
	return (1);
}

int	merge_quotes_with_surrounding(t_parse_context *ctx, char *q_c)
{
	char	*old;
	char	*temp;
	char	*final;

	if (!ctx || !ctx->last_token || !q_c || !*ctx->input)
		return (0);
	old = ctx->last_token->value;
	if (!old)
		return (0);
	temp = ft_strjoin_v2(old, q_c);
	if (!temp)
		return (free(q_c), ft_err_split(*ctx->cmd_lst, *ctx->head), 0);
	if (**ctx->input && **ctx->input != '$')
	{
		if (!h_quote_merge(ctx, &final, temp, q_c))
			return (0);
	}
	else
		final = temp;
	free(old);
	ctx->last_token->value = final;
	if (!ft_add_arguments(*ctx->current, final))
		return (free(q_c), ft_err_split(*ctx->cmd_lst, *ctx->head), 0);
	return (free(q_c), 1);
}

int	process_quote_merging(t_parse_context *ctx, char pr, char next, char *quote)
{
	int	ret;

	ret = 0;
	if (ctx->last_token && ctx->last_token->type == TOKEN_WORD
		&& !ft_isspace(next))
		ret = merge_quote_with_last(ctx, quote);
	else if ((ctx->last_token->next
			&& ctx->last_token->next->type == TOKEN_ENV_VAR) || next == '$')
		ret = add_quote_as_new_token(ctx, quote);
	else if (!ft_isspace(pr) && !ft_isspace(next) && pr != '<' && pr != '>'
		&& pr != '|')
	{
		if (pr == '-' && ctx->last_token && ctx->last_token->value[0] == '-')
			ret = merge_quotes_with_surrounding(ctx, quote);
		else
			ret = merge_quote_with_last(ctx, quote);
	}
	else if (!ft_isspace(pr) && ft_isspace(next) && pr != '<' && pr != '>'
		&& pr != '|')
		ret = merge_quote_with_last(ctx, quote);
	else if (ft_isspace(pr) && !ft_isspace(next))
		ret = handle_quote_with_next(ctx, quote);
	else
		ret = add_quote_as_new_token(ctx, quote);
	return (ret);
}

int	ft_handle_quotes(t_parse_context *ctx)
{
	const char	*qstart;
	char		pr;
	char		next;
	char		*quote;
	int			ret;

	if (!ctx || !ctx->input || !(*ctx->input))
		return (0);
	qstart = *ctx->input;
	pr = ' ';
	next = ' ';
	quote = build_quote_content(ctx);
	if (!quote)
		return (0);
	if (qstart > ctx->input_exec)
		pr = *(qstart - 1);
	if (**ctx->input)
		next = **ctx->input;
	ret = process_quote_merging(ctx, pr, next, quote);
	return (ret);
}
