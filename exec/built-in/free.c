#include "../include/exec.h"

void    free_char(char *str)
{
    if (str)
        free(str);
}

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

void free_env_list(t_env *head)
{
    t_env *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        if (tmp->key)
            free(tmp->key);
        if (tmp->value)
            free(tmp->value);
        free(tmp);
    }
}

void    free_node(t_env *node)
{
    if (!node)
        return ;
    if (node->key)
        free(node->key);
    if (node->value)
        free(node->value);
    free(node);
}

void	free_all(t_buit_in *exec)
{
    if (!exec)
        return ;
    free_char(exec->input);
	free_tab(exec->tab);
	free_list(&exec->env_cpy);
    free_list(&exec->export_cpy);
}
