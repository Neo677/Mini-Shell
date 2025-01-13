#include "built_in.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_list(t_env **lst)
{
    t_env *current;

    if (!lst)
        return ;
    current = *lst;
    while (current)
    {
        if (current->key)
            free(current->key);
        if (current->value)
            free(current->value);
        current = current->next;
    }
    free(current);
}

void	free_all(char **tab, t_env **lst)
{
	free_tab(tab);
	free_list(lst);
}