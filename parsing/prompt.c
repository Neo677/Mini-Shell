/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:13 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:14 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens(t_token *head)
{
	t_token		*current;
	const char	*token_type_name[] = 
	{
		[TOKEN_WORD] = "TOKEN_WORD", 
		[TOKEN_PIPE] = "TOKEN_PIPE", 
		[TOKEN_IN] = "TOKEN_IN", 
		[TOKEN_OUT] = "TOKEN_OUT",
		[TOKEN_APPEND] = "TOKEN_APPEND",
		[TOKEN_HEREDOC] = "TOKEN_HEREDOC",
		[TOKEN_ENV_VAR] = "TOKEN_ENV_VAR",
		[TOKEN_QUOTE] = "TOKEN_QUOTE",
		[TOKEN_DBL_QUOTE] = "TOKEN_DBL_QUOTE",
		[TOKEN_ERROR] = "TOKEN_ERROR",
	};
	current = head;
	while (current)
	{
		printf("Type: %s, Value: '%s'\n", token_type_name[current->type], current->value);
		current = current->next;
	}
}
