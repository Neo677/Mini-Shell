#include "built_in.h"

int    ft_swap(t_env *a, t_env *b)
{
    char    *temp_key;
    char    *temp_value;
    
    if (!a || !b)
        return (0);
    if (ft_strcmp(a->key, b->key) > 0)
    {
        temp_key = a->key;
        temp_value = a->value;

        a->key = b->key;
        a->value = b->value;

        b->key = temp_key;
        b->value = temp_value;
        return (1);
    }
    return (0);
}

t_env *sort_list(t_env **env_cpy)
{
    t_env *current;
    int swapped;

    current = *env_cpy;
    swapped = 1;
    while (swapped == 1)
    {
        swapped = 0;
        while (current)
        {
            if (ft_swap(current, current->next) == 1)
                swapped = 1;
            current = current->next;
        }
        current = *env_cpy;
    }
    return (*env_cpy);  
}

t_env   **export_cpy(t_env **env_cpy, t_env **cpy_env_cpy)
{
    t_env   *current;
    t_env   *current1;
    t_env   *new_node;

    current = *env_cpy;
    while (current)
    {
        new_node = create_node(current->key, current->value);
        if (!new_node)
        {
            free_env_list(cpy_env_cpy[0]);
            return (NULL);
        }
        if (cpy_env_cpy[0] == NULL)
            cpy_env_cpy[0] = new_node;
        else
        {
            current1 = cpy_env_cpy[0];
            while (current1->next != NULL)
                current1 = current1->next;
            current1->next = new_node;
        }
        current = current->next;
    }
    return (cpy_env_cpy);
}

void    ft_export(t_env **env_cpy1, char **key_value)
{
    t_env   *current;
    t_env   *new_node;
    t_env   **env_cpy;
    t_env   *cpy_env_cpy;
    char **tab;
    char    *value;
    int i;

    cpy_env_cpy = NULL;
    env_cpy = export_cpy(env_cpy1, &cpy_env_cpy);
    i = 0;
    if (!key_value[0])
    {
        sort_list(env_cpy);
        current = *env_cpy;
        while (current)
        {
            if ((current->key[0] >= 'a' && current->key[0] <= 'z') || (current->key[0] >= 'A' && current->key[0] <= 'Z') || current->key[0] == '_')
            {
                if (current->value)
                    printf("declare -x %s=\"%s\"\n", current->key, current->value);
                else
                    printf("declare -x %s\n", current->key);
            }
            current = current->next;
        }
        free_env_list(cpy_env_cpy);
        free_tab(key_value);
        return ;
    }
    while (key_value[i])
    {
        if ((key_value[i][0] >= 'a' && key_value[i][0] <= 'z') || (key_value[i][0] >= 'A' && key_value[i][0] <= 'Z') || key_value[i][0] == '_')
        {
            current = *env_cpy1;
            if (check_value(key_value[i]) == 0)
            {
                tab = split_in_two(key_value[i], '=');
                if (!tab)
                {
                    free_tab(key_value);
                    free_env_list(cpy_env_cpy);
                    return ;
                }
                if (search_by_key(env_cpy1, tab[0]) == 0)
                {
                    value = parse_value(tab[1]);
                    modify_node_value(env_cpy1, tab[0], value);
                    free_tab(tab);
                    free(value);
                }
                else
                {
                    new_node = create_key_value(key_value[i]);
                    if (!new_node)
                    {
                        free_tab(tab);
                        free_tab(key_value);
                        free_env_list(cpy_env_cpy);
                        return;
                    }
                    if (*env_cpy1 == NULL)
                        *env_cpy1 = new_node;
                    else
                    {
                        while (current->next)
                            current = current->next;
                        current->next = new_node;
                    }
                    free_tab(tab);
                }
            }
            else
            {
                if (search_by_key(env_cpy1, key_value[i]) == 0)
                    modify_node_value(env_cpy1, key_value[i], NULL);
                else
                {
                    new_node = create_key_value(key_value[i]);
                    if (!new_node)
                    {
                        free_tab(tab);
                        free_tab(key_value);
                        free_env_list(cpy_env_cpy);
                        return;
                    }
                    if (*env_cpy1 == NULL)
                        *env_cpy1 = new_node;
                    else
                    {
                        while (current->next)
                            current = current->next;
                        current->next = new_node;
                    }
                }
            }
        }
        else
        {
            ft_printf_fd(2, "bash: export: `%s': not a valid identifier\n", key_value[i]);
            free_env_list(cpy_env_cpy);
            free_tab(key_value);
            return;
        }  
        i++;   
    }
    // free_tab(key_value);
    free_env_list(cpy_env_cpy);
}


// enlever la ligne _=/usr/bin/env 
// mettre declare -x avant chaque variable
// mettre la valeur de chaque variable entre ""
// export z ='"'
// bash: export: `="': not a valid identifier
