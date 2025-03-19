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

static int	should_merge_tokens(const char *prev, const char *next)
{
	if (!prev || !next)
		return (0);
	// Si le token précédent commence par un tiret et le suivant est une lettre
	if (prev[0] == '-' && ft_isalpha(next[0]))
		return (1);
	// Si le token précédent se termine par une lettre et le suivant est une lettre
	if (ft_isalpha(prev[ft_strlen_v2(prev) - 1]) && ft_isalpha(next[0]))
		return (1);
	// Si le token précédent se termine par un tiret et le suivant commence par une lettre
	if (prev[ft_strlen_v2(prev) - 1] == '-' && ft_isalpha(next[0]))
		return (1);
	// Si le token précédent se termine par une lettre et le suivant commence par un tiret
	if (ft_isalpha(prev[ft_strlen_v2(prev) - 1]) && next[0] == '-')
		return (1);
	// Si le token précédent se termine par une lettre et le suivant est une lettre
	// (cas spécial pour les options après une quote)
	if (ft_isalpha(prev[ft_strlen_v2(prev) - 1]) && ft_isalpha(next[0]))
		return (1);
	// Si le token précédent se termine par une lettre et le suivant est une lettre
	// (cas spécial pour les options après une quote)
	if (prev[ft_strlen_v2(prev) - 1] == '-' && ft_isalpha(next[0]))
		return (1);
	return (0);
}

static char	*merge_tokens(char *prev, char *next)
{
	char	*result;
	int		len;

	len = ft_strlen_v2(prev) + ft_strlen_v2(next) + 1;
	result = malloc(sizeof(char) * len);
	if (!result)
		return (NULL);
	ft_strlcpy(result, prev, ft_strlen_v2(prev) + 1);
	ft_strlcat(result, next, len);
	return (result);
}

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

int	merge_quote_with_last(t_parse_context *ctx, char *quote_content)
{
	char	*new;

<<<<<<< Updated upstream
	new = ft_strjoin_v2(ctx->last_token->value, quote_content);
=======
	if (ctx->last_token && should_merge_tokens(ctx->last_token->value, quote_content))
	{
		new = merge_tokens(ctx->last_token->value, quote_content);
		if (!new)
		{
			free(quote_content);
			ft_err_split(*ctx->cmd_lst, *ctx->head);
			return (0);
		}
		old = ctx->last_token->value;
		ctx->last_token->value = new;
		free(old);
		free(quote_content);
		ctx->last_token = ft_last_token(*ctx->head);
		return (1);
	}

	old = ctx->last_token->value;
	new = ft_strjoin_v2(old, quote_content);
>>>>>>> Stashed changes
	if (!new)
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	ctx->last_token->value = new;
	printf("{merge_quote_with_last} quote_content: %s\n", quote_content);
	if (!ft_add_arguments(*ctx->current, quote_content))
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
	ctx->last_token = ft_last_token(*ctx->head);
	return (free(quote_content), 1);
}

int	add_quote_as_new_token(t_parse_context *ctx, char *quote_content)
{
	t_token	*token;

	token = ft_create_token(TOKEN_WORD, quote_content);
	ft_add_token(ctx->head, token);
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	printf("{add_quote_as_new_token} quote_content: %s\n", quote_content);
	if (!ft_add_arguments(*ctx->cmd_lst, quote_content))
	{
		free(quote_content);
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		return (0);
	}
<<<<<<< Updated upstream
	ctx->last_token = ft_last_token(*ctx->head);
=======
	ctx->last_token = token;
>>>>>>> Stashed changes
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
	char		*quote;
	int			ret;

	quote = build_quote_content(ctx);
	if (!quote)
		return (0);
<<<<<<< Updated upstream
	ret = 0;
	ret = add_quote_as_new_token(ctx, quote);
=======
	printf("DEBUG: quote content: %s\n", quote);
	if (ctx->last_token)
	{
		printf("DEBUG: last_token type: %d\n", ctx->last_token->type);
		printf("DEBUG: last_token value: %s\n", ctx->last_token->value);
	}
	else
		printf("DEBUG: last_token is NULL\n");
	if (ctx->last_token && ctx->last_token->type == TOKEN_WORD)
	{
		printf("DEBUG: should_merge_tokens result: %d\n", 
			should_merge_tokens(ctx->last_token->value, quote));
		if (should_merge_tokens(ctx->last_token->value, quote))
		{
			printf("DEBUG: Attempting to merge tokens\n");
			ret = merge_quote_with_last(ctx, quote);
		}
		else
		{
			printf("DEBUG: Creating new token\n");
			ret = add_quote_as_new_token(ctx, quote);
		}
	}
	else
	{
		printf("DEBUG: No last token or not TOKEN_WORD, creating new token\n");
		ret = add_quote_as_new_token(ctx, quote);
	}
	ctx->last_token = ft_last_token(*ctx->head);
>>>>>>> Stashed changes
	return (ret);
}
