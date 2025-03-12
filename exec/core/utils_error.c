/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:49:09 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:49:10 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char	*ft_join_pipex(char *join, char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	return (join);
}

char	*ft_strjoin_pipex(char *s1, char *s2)
{
	char	*join;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	join = malloc(sizeof(char) * (ft_strlen_pipex(s1) + ft_strlen_pipex(s2)
				+ 1));
	if (!join)
		return (NULL);
	return (ft_join_pipex(join, s1, s2));
}
