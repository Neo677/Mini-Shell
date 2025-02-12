#include "built_in.h"

int skip_space(char *str, int i)
{
  while (str[i] && str[i] == ' ')
    i++;
  return (i);
}

int skip_built(char *str, int i)
{
  while (str[i] && str[i] == ' ')
    i++;
  while (str[i] && str[i] != ' ')
    i++;
  return (i);
}

int check_space(char *str, int i)
{
  while (str[i])
  {
    if (str[i] != ' ')
      return (1);
    i++;
  }
  return (0);
}

int	count_export_var(char *str)
{
	int	count;
	int	i;
	char	quote;

	count = 0;
  i = 0;
	// i = skip_built(str, 0);
  quote = 0;
  // if (check_space(str, i) == 0)
  //   return (0);
  // printf("str = %s\n", str);
	while (str[i])
	{
		while (str[i])
		{
			if (!quote && (str[i] == '\'' || str[i] == '\"'))
				quote = str[i];
			else if (quote && str[i] == quote)
				quote = 0;
			else if (!quote && str[i] == ' ')
			{
				count++;
				break;
			}
			i++;
		}
		while (str[i] == ' ')
			i++;
	}
	return (count);
}

char  **tab_export(char *str)
{
  char  **tab;
  int i;
  int j;
  int k;
  int start;
  char quote;

  tab = malloc(sizeof(char *) * (count_export_var(str) + 1));
  if (!tab)
    return (NULL);
  i = skip_built(str, 0);
  j = 0;
  quote = 0;
  while (j < count_export_var(str))
  {
    while (str[i] == ' ')
      i++;
    start = i;
    if (str[start] == '\\')
      start++;
    while (str[i])
		{
			if (!quote && (str[i] == '\'' || str[i] == '\"'))
				quote = str[i];
			else if (quote && str[i] == quote)
				quote = 0;
			else if (!quote && str[i] == ' ')
				break;
			i++;
		}
    tab[j] = malloc(sizeof(char) * (i - start + 1));
    if (!tab[j])
    {
      free_tab(tab);
      return (NULL);
    }
    k = 0;
    while (start < i)
      tab[j][k++] = str[start++];
    tab[j][k] = '\0';
    j++;
  }
  tab[j] = NULL;
  return (tab);
}
