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

void	ft_error_pipe(const char *context)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
		context);
}

void	ft_error_redirections(const char *context)
{
	ft_printf_fd(2, "minishell: syntax error near unexpected token `%s'\n",
		context);
}

int	ft_error_quote(void)
{
	ft_printf_fd(2, "minishell: syntax error: unclosed quote\n");
	return (1);
}

int	ft_error_general(const char *context)
{
	ft_printf_fd(2, "minishell: %s\n", context);
	return (1);
}

int	ft_error_env(const char *context)
{
	ft_printf_fd(2, "minishell: '%s': invalid environment variable\n", context);
	return (1);
}
