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
	t_token	*current;

	current = head;
	while (current)
	{
		printf("[TOKEN] Type: %d, Value: '%s'\n", current->type,
			current->value);
		current = current->next;
	}
}
