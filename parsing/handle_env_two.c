/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:26:01 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/11 14:26:02 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_replace_dol(char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	quest;

	i = 0;
	j = 0;
	quest = 0;
	while (var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '$')
		{
			while (var_value[j])
			{
				j++;
			}
			if (j == 1)
				quest++;
		}
		i++;
	}
	i += j - 2;
	return (i + quest);
}

int	count_replace_quest(char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	quest;

	i = 0;
	j = 0;
	quest = 0;
	while (var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '?')
		{
			while (var_value[j])
				j++;
			if (j == 1)
				quest++;
		}
		i++;
	}
	i += j - 2;
	return (i + quest);
}

int	fill_result_quest(char *result, char *var_value, char *var_name)
{
	int	i;
	int	j;
	int	k;
	int	quest;

	i = 0;
	j = 0;
	k = 0;
	quest = 0;
	while (var_name[i])
	{
		if (var_name[i] == '$' && var_name[i + 1] == '?')
		{
			if (var_name[i + 2])
				i += 2;
			while (var_value[j])
				result[k++] = var_value[j++];
			if (j == 1 && !var_name[i])
				quest++;
		}
		if (i == 0)
			return (result[k] = '\0', 0);
		result[k++] = var_name[i++ + quest];
	}
	return (result[k] = '\0', 0);
}

char	*replace_quest(char *var_value, char *var_name)
{
	char	*result;

	result = malloc(sizeof(char) * count_replace_quest(var_value, var_name)
			+ 1);
	if (!result)
		return (NULL);
	fill_result_quest(result, var_value, var_name);
	return (result);
}
