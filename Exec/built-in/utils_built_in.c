#include "built_in.h"

int ft_strlen(char *s)
{
    int i;

    i = 0;
    while(s[i])
        i++;
    return (i);
}

char    *ft_strdup(char *src)
{
    char *dst;
    int j;
    int i;
	int	len;

    len = ft_strlen(src);
    dst = malloc(sizeof(char) * len + 1);
    if(!dst)
    {
        return (0);
    }
	j = 0;
    i = 0;
    while (src[i])
    {
        dst[j] = src[i];
        i++;
        j++;
    }
    dst[j] = '\0';
    return (dst);
}

int ft_strcmp(char *s1, char *s2)
{
    int i;

    i = 0;
    if (!s1)
        return (1);
    while (s1[i] || s2[i])
    {
        if (s1[i] != s2[i])
            return (s1[i] - s2[i]);
        i++;
    }
    return (0);
}

char	*ft_join(char *join, char *s1, char *s2)
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

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	return (ft_join(join, s1, s2));
}

// char	*ft_strchr(const char *s, int c)
// {
// 	if (s == NULL)
// 		return (NULL);
// 	while (*s)
// 	{
// 		if (*s == (char)c)
// 			return ((char *)s);
// 		s++;
// 	}
// 	return (NULL);
// }