/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:11:47 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/04 17:11:48 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(const char *error)
{
	ft_printf("🚨  %s  🚨\n", error);
	exit(EXIT_FAILURE);
}

void	ft_free_token(t_token *token)
{
	t_token *tmp;
	while(token)
	{ 
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}


