/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:33:38 by thobenel          #+#    #+#             */
/*   Updated: 2024/05/06 16:05:53 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_my_word(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static char	*f_strdup(const char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	str = (char *)ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
/*F pour dulpliquer une sous chaine jusque a c
alloc pour la new chaine pour init a 0*/

char	**ft_split(char const *s, char c)
{
	int		count_word;
	int		i;
	char	**rst;

	if (!s)
		return (0);
	count_word = count_my_word(s, c);
	rst = (char **)ft_calloc(count_word + 1, sizeof(char *));
	if (!rst)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			rst[i++] = f_strdup(s, c);
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	rst[i] = NULL;
	return (rst);
}
/* F pp qui permet de decouper S en mots compte les mots dans S 
duplique la chaine jusque au delimiateur alloc pour tableau de pointeur
termine le tableau de la chaine par NULL.*/