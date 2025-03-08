/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:46 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:48 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_valid_redirections(const t_token *token)
{
    while (token)
    {
        if (token->type == TOKEN_IN || token->type == TOKEN_OUT ||
            token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
        {
            if (!token->next || token->next->type != TOKEN_WORD)
            {
                ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token\n");
                return (0);
            }
        }
        token = token->next;
    }
    return (1);
}

char *ft_valid_quotes(char **current, char quote_type) 
{
    char *start;
    char *value;
    size_t len = 0;

    if (!current || !*current || !**current) 
    {
        ft_error_quote();
        return (NULL);
    }

    (*current)++;
    start = *current;

    while (**current && **current != quote_type) 
    {
        if (**current == '\\' && (quote_type == '\"') &&
            (*(*current + 1) == quote_type || *(*current + 1) == '\\')) 
        {
            (*current)++;
        }
        (*current)++;
        len++;
    }
    if (**current == '\0') 
    { 
        ft_error_quote();
        return (NULL);
    }

    value = ft_strndup(start, len);
    if (!value) 
    {
        ft_printf_fd(STDERR_FILENO, "minishell: memory allocation failed\n");
        return (NULL);
    }

    (*current)++;
    return (value);
}

int ft_validay_quotes(t_token *token)
{
    char *parsed_value;

    if (token->type == TOKEN_QUOTE || token->type == TOKEN_DBL_QUOTE)
    {
        parsed_value = ft_valid_quotes(&token->value, token->type);
        if (!parsed_value)
        {
            ft_printf_fd(STDERR_FILENO, "minishell: syntax error: unclosed quote\n");
            return (0);
        }
        free(parsed_value);
    }
    return (1);
}

int ft_validate_pipes(t_token *token, t_parse_context *ctx)
{
    t_token *prev;
    
    prev = NULL;
    (void)ctx;
    if (!token || token->type == TOKEN_PIPE)
        return (ctx->exit_status = 0, 0);

    while (token) 
    {
        if (token->type == TOKEN_PIPE) 
        {
            if (!prev || prev->type == TOKEN_PIPE) 
            {
                ctx->exit_status = 2;
                return (ft_printf_fd(STDERR_FILENO, "1minishell: syntax error near unexpected token `|'\n"), 0);
            }
            if (!token->next)
            {
                ctx->exit_status = 2;
                return (ft_printf_fd(STDERR_FILENO, "2minishell: syntax error: pipe at the end\n"), 0);
            }
                
        }
        prev = token;
        token = token->next;
    }
    return (1);
}

static bool ft_is_empty_string(const char *str)
{
    if (!str)
        return (true);
    while (*str)
    {
        if (!ft_isspace(*str))
            return (false);
        str++;
    }
    return (true);
}

int ft_valid_env_var(t_token *token)
{
    if (!token)
        return (1);
        
    while (token)
    {
        if (token->type == TOKEN_ENV_VAR)
        {
            if (!token->value || ft_is_empty_string(token->value))
            {
                ft_printf_fd(STDERR_FILENO, "minishell: invalid environment variable syntax\n");
                return (0);
            }
            if (ft_strchr(token->value, '$') && ft_strlen(token->value) == 1)
            {
                ft_printf_fd(STDERR_FILENO, "minishell: $: ambiguous redirect\n");
                return (0);
            }
        }
        token = token->next;
    }
    return (1);
}
int ft_valid_token(t_token *token, t_parse_context *ctx) 
{
    t_token *current = token;
    
    if (!ft_validate_pipes(current, ctx))
    {
        return (0);
    }    
    if (!ft_valid_redirections(current))
    {
        ctx->exit_status = 2;
        return (0);
    }    
    if (!ft_valid_env_var(current))
    {
        ctx->exit_status = 2;
        return (0);
    }    
    while (current != NULL)
    {
        if (!ft_validay_quotes(current))
        {
            ctx->exit_status = 2;
            return (0);
        }
        current = current->next;
    }
    return (1);
}
