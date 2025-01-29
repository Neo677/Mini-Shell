#include "built_in.h"

void    free_char(char *str)
{
    if (str)
        free(str);
}

// void	free_tab(char **tab)
// {
// 	int	i;

// 	if (!tab)
// 		return ;
// 	i = 0;
// 	while (tab[i])
// 	{
// 		free(tab[i]);
// 		i++;
// 	}
// 	free(tab);
// }

void	free_list(t_env **lst)
{
    t_env *current;
    t_env   *next;

    if (!lst || !*lst)
        return ;
    current = *lst;
    while (current)
    {
        next = current->next;
        if (current->key)
            free(current->key);
        if (current->value)
            free(current->value);
        free(current);
        current = next;
    }
    *lst = NULL;
}

void	free_all_builtin(t_built_in *exec)
{
    if (!exec)
        return ;
    free_char(exec->input);
	// free_tab(exec->tab);
	free_list(&exec->env_cpy);
    free_list(&exec->export_cpy);
}