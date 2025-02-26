#include "minishell.h"

int ft_handle_space(t_parse_context *ctx, char *quote_content)
{
    char *new;
    
    new = ft_strjoin_v2(ctx->last_token->value, quote_content);
    if (!new)
        return (0);
    ctx->last_token->value = new;
    if (!ft_add_arguments(*ctx->current, quote_content))
        return (0);
    return (1);
}

// int	ft_handle_quotes(t_parse_context *ctx)
// {
// 	char		*quote_content;
// 	const char	*input_ptr;
// 	char		prev_char;
// 	char		*new;

// 	input_ptr = *ctx->input;
// 	quote_content = ft_handle_quote(ctx);
// 	if (!quote_content)
// 		return (0);
// 	if (input_ptr > ctx->input_exec)
// 		prev_char = *(input_ptr - 1);
// 	else
// 		prev_char = ' ';
// 	if (!ft_isspace(prev_char) && ctx->last_token && ctx->last_token->value)
// 	{
// 		new = ft_strjoin_v2(ctx->last_token->value, quote_content);
// 		if (!new)
// 		{
// 			ft_err_split(*ctx->cmd_lst, *ctx->head);
// 			return (0);
// 		}
// 		/* On remplace la valeur du token précédent par la nouvelle chaîne.
// 		   Ces fonctions prennent la propriété de la chaîne quote_content. */
// 		ctx->last_token->value = new;
// 		if (!ft_add_arguments(*ctx->current, quote_content))
// 		{
// 			ft_err_split(*ctx->cmd_lst, *ctx->head);
// 			return (0);
// 		}
// 		/* On ne libère pas quote_content ici car il sera libéré lors du free du token. */
// 		return (1);
// 	}
// 	ft_add_token(ctx->head, ft_create_token(TOKEN_WORD, quote_content));
// 	if (!*ctx->current)
// 		*ctx->current = ft_init_command(ctx->cmd_lst);
// 	if (!ft_add_arguments(*ctx->cmd_lst, quote_content))
// 	{
// 		ft_err_split(*ctx->cmd_lst, *ctx->head);
// 		return (0);
// 	}
// 	ctx->last_token = ft_last_token(*ctx->head);
// 	/* On ne libère pas quote_content ici non plus, car il est désormais géré par le token */
// 	return (1);
// }

int ft_handle_quotes(t_parse_context *ctx)
{
    char *quote_content;
    const char *input_ptr;
    char prev_char;
    char *new;

    input_ptr = *ctx->input;
    quote_content = ft_handle_quote(ctx);
    if (!quote_content)
        return (0);
    if (input_ptr > ctx->input_exec)
        prev_char = *(input_ptr - 1);
    else
        prev_char = ' ';
    if (!ft_isspace(prev_char) && ctx->last_token && ctx->last_token->value)
    {
        new = ft_strjoin_v2(ctx->last_token->value, quote_content);
        if (!new)
            return (free(quote_content), ft_err_split(*ctx->cmd_lst, *ctx->head), 0);
        ctx->last_token->value = new;
        if (!ft_add_arguments(*ctx->current, quote_content))
            return (free(quote_content), ft_err_split(*ctx->cmd_lst, *ctx->head), 0);
        return (free(quote_content), 1);
        if (!ft_handle_space(ctx, quote_content))
            return (free(quote_content), ft_err_split(*ctx->cmd_lst, *ctx->head), 0);
        return (free(quote_content), 1);
    }
    ft_add_token(ctx->head, ft_create_token(TOKEN_WORD, quote_content));
    if (!*ctx->current)
        *ctx->current = ft_init_command(ctx->cmd_lst);
    if (!ft_add_arguments(*ctx->cmd_lst, quote_content))
        return (free(quote_content), ft_err_split(*ctx->cmd_lst, *ctx->head), 0);
    ctx->last_token = ft_last_token(*ctx->head);
    return (free(quote_content), 1);
}
