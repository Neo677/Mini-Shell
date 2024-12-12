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
	printf(" [🚨ERROR 🚨] pipe error minishell = '%s'\n", context);
}

int	ft_error_redirections(const char *context)
{
	printf(" [🚨ERROR🚨]redirec syntax error unexpected token '%s'\n", context);
	return (0);
}

int	ft_error_quote(void)
{
	printf(" [🚨ERROR🚨] quote minishell : syntax error = unclosed quote\n");
	return (0);
}

int	ft_error_general(const char *context)
{
	printf(" [🚨ERROR🚨] gen minishell : error = %s\n", context);
	return (0);
}

int	ft_error_env(const char *context)
{
	printf(" [🚨ERROR🚨] gen minishell : error = %s\n", context);
	return (0);
}
