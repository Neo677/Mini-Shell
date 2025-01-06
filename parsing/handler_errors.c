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
	printf(" [🚨 ERROR 🚨] pipe = '%s'\n", context);
	return (0);
}

int	ft_error_redirections(const char *context)
{
	printf(" [🚨ERROR🚨]redirection syntax = '%s'\n", context);
	return (0);
}

int	ft_error_quote(void)
{
	printf(" [🚨ERROR🚨] quote syntax = unclosed quote\n");
	return (0);
}

int	ft_error_general(const char *context)
{
	printf(" [🚨ERROR🚨] general = %s\n", context);
	return (0);
}

int	ft_error_env(const char *context)
{
	printf(" [🚨ERROR🚨] env_var minishell = %s\n", context);
	return (0);
}
