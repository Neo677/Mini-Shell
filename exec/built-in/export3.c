/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:38 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:47:39 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	ft_swap(t_env *a, t_env *b)
{
	char	*temp_key;
	char	*temp_value;

	if (!a || !b)
		return (0);
	if (ft_strcmp(a->key, b->key) > 0)
	{
		temp_key = a->key;
		temp_value = a->value;
		a->key = b->key;
		a->value = b->value;
		b->key = temp_key;
		b->value = temp_value;
		return (1);
	}
	return (0);
}

t_env	*sort_list(t_env **env_cpy)
{
	t_env	*current;
	int		swapped;

	current = *env_cpy;
	swapped = 1;
	while (swapped == 1)
	{
		swapped = 0;
		while (current)
		{
			if (ft_swap(current, current->next) == 1)
				swapped = 1;
			current = current->next;
		}
		current = *env_cpy;
	}
	return (*env_cpy);
}

t_env	**export_cpy(t_env **env_cpy, t_env **cpy_env_cpy)
{
	t_env	*current;
	t_env	*current1;
	t_env	*new_node;

	current = *env_cpy;
	while (current)
	{
		new_node = create_node(current->key, current->value);
		if (!new_node)
		{
			free_env_list(cpy_env_cpy[0]);
			return (NULL);
		}
		if (cpy_env_cpy[0] == NULL)
			cpy_env_cpy[0] = new_node;
		else
		{
			current1 = cpy_env_cpy[0];
			while (current1->next != NULL)
				current1 = current1->next;
			current1->next = new_node;
		}
		current = current->next;
	}
	return (cpy_env_cpy);
}
