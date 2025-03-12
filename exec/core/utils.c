/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:49:13 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:49:14 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	ft_strchr_exec(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen_exec(int nb)
{
	int	len;

	len = 1;
	while (nb > 9)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

int	ft_strlen_pipex(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_itoa_exec(int nbr)
{
	char	*str;
	int		len;
	int		i;

	len = ft_strlen_exec(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	str[len] = '\0';
	while (i < len)
	{
		len--;
		str[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

int	count_cmd(t_command *cmd)
{
	t_command	*current;
	int			i;

	i = 0;
	current = cmd;
	while (current)
	{
		i++;
		current = current->next;
	}
	return (i);
}
