/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_token_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:23:18 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:23:28 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_valid_redirections(const t_token *token)
{
	while (token)
	{
		if (token->type == TOKEN_IN || token->type == TOKEN_OUT
			|| token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
		{
			if (!token->next || token->next->type != TOKEN_WORD)
			{
				ft_printf_fd(STDERR_FILENO,
					"minishell: syntax error near unexpected token\n");
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}

static bool	ft_is_empty_string(const char *str)
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

int	ft_valid_env_var(t_token *token)
{
	if (!token)
		return (1);
	while (token)
	{
		if (token->type == TOKEN_ENV_VAR)
		{
			if (!token->value || ft_is_empty_string(token->value))
			{
				ft_printf_fd(STDERR_FILENO,
					"minishell: invalid environment variable syntax\n");
				return (0);
			}
		}
		token = token->next;
	}
	return (1);
}
