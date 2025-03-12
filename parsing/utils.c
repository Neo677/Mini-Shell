/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:12:14 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/12 21:48:26 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strnlen(const char *s, size_t max)
{
	size_t	i;

	i = 0;
	while (s[i] && i < max)
		i++;
	return (i);
}

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (src[i] && i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strndup(const char *src, size_t size)
{
	char	*dst;
	size_t	len;

	len = ft_strnlen(src, size);
	dst = (char *)malloc(len + 1);
	if (!dst)
		return (NULL);
	ft_strncpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}

int	ft_strcmp_parsing(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*extract_str(char *var_name)
{
	int		i;
	char	*new_str;

	i = 0;
	while (var_name[i] && var_name[i] != ' ')
		i++;
	new_str = malloc(sizeof(char) * i + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (var_name[i] && var_name[i] != ' ')
	{
		new_str[i] = var_name[i];
		i++;
	}
	new_str[i] = '\0';
	free(var_name);
	return (new_str);
}
