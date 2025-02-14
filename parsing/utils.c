/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:12:14 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/04 17:12:16 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_strnlen(const char *s, size_t max)
{
    size_t i;

    i = 0;
    while (s[i] && i < max)
        i++;
    return (i);
}

char *ft_strncpy(char *dst, const char *src, size_t len)
{
    size_t i;

    i = 0;
    while (src[i] && i < len)
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

char *ft_strndup(const char *src, size_t size)
{
    char *dst;
    size_t len = ft_strnlen(src, size);

    dst = (char *)malloc(len + 1);
    if (!dst)
        return (free(dst), NULL);
    ft_strncpy(dst, src, len);
    dst[len] = '\0';
    return (dst);
}

int ft_strcmp_parsing(char *s1, char *s2)
{
	int i = 0;

	while((s1[i] == s2[i]) && s1[i] && s2[i])
		i++;
	return (s1[i]-s2[i]);
}

char    *replace_with_space(char *str)
{
    char    *new_str;
    int i;
    int j;

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

int check_variable_backslash_n_parse(char *value)
{
    int i;

    i = 0;
    while (value[i])
    {
        if (value[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

int 	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}