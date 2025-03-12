/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:24 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:47:25 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	ft_env(t_env **env_cpy)
{
	t_env	*current;

	current = *env_cpy;
	while (current)
	{
		if (current->val != 1)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
