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
    char    *quote_content;
    char    *prefix;

    prefix = ft_strdup_v2_quote(*ctx->input);
    printf("Préfixe: %s\n", prefix);
    
    // Extraire le contenu entre quotes
    quote_content = ft_handle_quote(ctx);
    if (!quote_content)
    {
        free(prefix);
        return (0);
    }
    char *combined = ft_strjoin(prefix, quote_content);
    free(prefix);
    if (!combined)
    {
        free(quote_content);
        return (0);
    }
    if (*ctx->input && !ft_isspace(**ctx->input))
    {
        char *rest = ft_get_next_token(ctx->input);
        char *merged = ft_strjoin(combined, rest);
        free(rest);
        free(combined);
        if (!merged)
            return (0);
        return (merge_quote_with_last(ctx, merged));
    }
    else
    {
        free(quote_content);
        free(combined);
        return (add_quote_as_new_token(ctx, combined));
    }
}
