/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:14 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:47:15 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	check_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (0);
		i++;
	}
	return (1);
}

char	*parse_value(char *input)
{
	char	*result;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	result = malloc(ft_strlen(input) + 1);
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (!quote && (input[i] == '\'' || input[i] == '\"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		else
			result[j++] = input[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

char	**init_create_key_value(char *env)
{
	char	**tab;

	tab = split_in_two(env, '=');
	if (!tab)
		return (NULL);
	return (tab);
}

t_env	*create_key_value(char *env)
{
	t_env	*node;
	char	**tab;

	if (check_value(env) == 0)
	{
		tab = init_create_key_value(env);
		node = create_node(tab[0], tab[1]);
		if (!node)
		{
			free_tab(tab);
			return (NULL);
		}
		free_tab(tab);
	}
	else
		node = create_node(env, NULL);
	return (node);
}

void	copy_env(char **env, t_env **env_cpy)
{
	t_env	*new_node;
	t_env	*current;
	int		i;

	i = 0;
	while (env[i])
	{
		new_node = create_key_value(env[i]);
		if (!new_node)
			return ;
		if (env_cpy[0] == NULL)
			env_cpy[0] = new_node;
		else
		{
			current = env_cpy[0];
			while (current->next != NULL)
				current = current->next;
			current->next = new_node;
		}
		i++;
	}
}
