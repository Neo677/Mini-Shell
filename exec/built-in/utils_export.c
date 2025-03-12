/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:14 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:48:15 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	check_key_export(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9') || str[i] == '\\'
			|| str[i] == '_')
		{
			if (str[i] == '\\' && str[i + 1] == '\\')
				return (1);
			i++;
		}
		else
			return (1);
	}
	return (0);
}

char	*init_remove_backslash(char *str)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			len++;
		i++;
	}
	new_str = malloc(sizeof(char) * (ft_strlen(str) - len + 1));
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*remove_backslash(char *str)
{
	int		i;
	int		j;
	int		egal;
	char	*new_str;

	new_str = init_remove_backslash(str);
	i = 0;
	j = 0;
	egal = 0;
	while (str[i])
	{
		if (str[i] == '=')
			egal = 1;
		if (str[i] == '\\' && egal == 0)
			i++;
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*replace_b_n(char *value)
{
	char	*new_value;
	int		i;
	int		j;

	new_value = malloc(sizeof(char) * ft_strlen(value) + ft_count(value, '\n')
			+ 1);
	if (!new_value)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i])
	{
		if (value[i] == '\n')
		{
			new_value[j] = '\\';
			j++;
			new_value[j] = 'n';
			i++;
			j++;
		}
		new_value[j] = value[i];
		j++;
		i++;
	}
	return (new_value);
}

int	check_b_n(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}
