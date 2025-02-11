
// #include "../include/pipex.h"
#include "../built-in/built_in.h"

// int	ft_count(char *s, char c)
// {
// 	int	i;
// 	int	count;
// 	int	onoff;

// 	i = 0;
// 	count = 0;
// 	onoff = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && onoff == 0)
// 		{
// 			count++;
// 			onoff = 1;
// 		}
// 		else
// 			onoff = 0;
// 		i++;
// 	}
// 	return (count);
// }

// int	ft_len(char *str, char c, int i)
// {
// 	int	j;

// 	j = 0;
// 	while (str[i] && str[i] != c)
// 	{
// 		i++;
// 		j++;
// 	}
// 	return (j);
// }

char	**ft_split_init(char *str, char c, char **tab)
{
	int	i;
	int	j;
	int	start;

	i = 0;
	start = 0;
	while (str[i] && start < ft_count_pipex(str, c))
	{
		while (str[i] == c)
			i++;
		tab[start] = malloc(sizeof(char) * ft_len_pipex(str, c, i) + 1);
		if (!tab[start])
			return (NULL);
		j = 0;
		while (str[i] && str[i] != c)
			tab[start][j++] = str[i++];
		tab[start][j] = '\0';
		start++;
	}
	tab[start] = NULL;
	return (tab);
}

char	**ft_split_built(char *str, char c)
{
	char	**tab;
	int		words;

	words = ft_count_pipex(str, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	tab = ft_split_init(str, c, tab);
	return (tab);
}
