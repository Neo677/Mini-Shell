/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:56 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:47:57 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	ft_strlen_c(char *str, int i, char c)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char	**init_split_in_two(char *str, char c)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	tab[0] = NULL;
	tab[1] = NULL;
	tab[2] = NULL;
	tab[0] = malloc(sizeof(char) * ft_strlen_c(str, 0, c) + 1);
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}

char	**split_in_two(char *str, char c)
{
	int		i;
	int		j;
	char	**tab;

	tab = init_split_in_two(str, c);
	i = 0;
	j = 0;
	while (str[i] && str[i] != c)
		tab[0][j++] = str[i++];
	tab[0][j] = '\0';
	i++;
	tab[1] = malloc(sizeof(char) * ft_strlen_c(str, i, '\0') + 1);
	if (!tab[1])
	{
		free_tab(tab);
		return (NULL);
	}
	j = 0;
	while (str[i])
		tab[1][j++] = str[i++];
	tab[1][j] = '\0';
	return (tab);
}
