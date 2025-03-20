/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:49:20 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/20 10:32:07 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	ft_strlen_dp(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	clear_file(char **filename)
{
	int	i;

	i = 0;
	if (!filename)
		return ;
	while (filename[i])
	{
		if (filename[i] && access(filename[i], F_OK) == 0)
			unlink(filename[i]);
		free(filename[i]);
		i++;
	}
	free(filename);
}

int	str_search(char *big, char *little, int len)
{
	int	i;

	i = 0;
	while ((big[i] || little[i]) && i < len)
	{
		if (big[i] != little[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strcpy(char *dst, char *cpy)
{
	int	i;

	i = 0;
	while (cpy[i])
	{
		dst[i] = cpy[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strcat(char *dst, char *src)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (dst);
}
