/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:23:42 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:23:43 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_with_space_parse(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new_str)
		return (str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			new_str[j] = ' ';
		else
			new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (new_str);
}

int	check_variable_backslash_n_parse(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}
