/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:41 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:24:42 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_pipe(const char *context)
{
	ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `%s`", context);
	return (258);
}

int	ft_error_redirections(const char *context)
{
	ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `%s`", context);
	return (258);
}

int	ft_error_quote(void)
{
	ft_printf_fd(STDERR_FILENO, "minishell: syntax error: unclosed quote\n");
	return (258);
}

int	ft_error_general(const char *context)
{
	ft_printf_fd(STDERR_FILENO, "minishell: %s\n", context);
	return (1);
}

int	ft_error_env(const char *context)
{
	ft_printf_fd(STDERR_FILENO, "minishell: '%s': invalid environment variable\n", context);
	return (1);
}
