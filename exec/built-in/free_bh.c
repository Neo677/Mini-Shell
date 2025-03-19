/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:42 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/14 13:01:32 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	free_char(char *str)
{
	if (str)
		free(str);
}

void	free_list(t_env **lst)
{
	t_env	*current;
	t_env	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		if (current->key)
			free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	free_env_list(t_env *head)
{
	t_env	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		free(head);
		head = tmp;
	}
}

void	free_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_all(t_buit_in *exec)
{
	if (!exec)
		return ;
	if (exec->input)
		free_char(exec->input);
	if (exec->tab)
		free_tab(exec->tab);
	if (exec->env_cpy)
		free_list(&exec->env_cpy);
	if (exec->export_cpy)
		free_list(&exec->export_cpy);
}
