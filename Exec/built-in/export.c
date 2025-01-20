#include "built_in.h"

int    ft_swap(t_env *a, t_env *b)
{
    char    *temp_key;
    char    *temp_value;
    
    if (!a || !b)
        return (0);
    if (ft_strcmp_exec(a->key, b->key) > 0)
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
            return (NULL);
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

// void    ft_export(t_env **env_cpy1, char *key_value)
// {
//     t_env   *current;
//     t_env   *new_node;
//     t_env   **env_cpy;
//     t_env   *cpy_env_cpy;

//     cpy_env_cpy = NULL;
//     env_cpy = export_cpy(env_cpy1, &cpy_env_cpy);
//     if (!key_value)
//     {
//         sort_list(env_cpy);
//         current = *env_cpy;
//         while (current)
//         {
//             printf("declare -x %s=\"%s\"\n", current->key, current->value);
//             current = current->next;
//         }
//     }
//     else
//     {
//         if ((key_value[0] >= 'a' && key_value[0] <= 'z') || (key_value[0] >= 'A' && key_value[0] <= 'Z'))
//         {
//             new_node = create_key_value(key_value);
//             current = *env_cpy;
//             if (*env_cpy == NULL)
//                 *env_cpy = new_node;
//             else
//             {
//                 while (current->next)
//                     current = current->next;
//                 current->next = new_node;
//             }  
//         }
//         else
//         {
//             ft_printf(2, "bash: export: `%s': not a valid identifier\n", key_value);
//             return ;
//         }     
//     }
// }


void    ft_export(t_env **env_cpy1, char *key_value)
{
    t_env   *current;
    t_env   *new_node;
    t_env   **env_cpy;
    t_env   *cpy_env_cpy;

    cpy_env_cpy = NULL;
    env_cpy = export_cpy(env_cpy1, &cpy_env_cpy);
    if (!key_value)
    {
        sort_list(env_cpy);
        current = *env_cpy;
        while (current)
        {
            if ((current->key[0] >= 'a' && current->key[0] <= 'z') || (current->key[0] >= 'A' && current->key [0] <= 'Z'))
            {
                if (current->value)
                    printf("declare -x %s=\"%s\"\n", current->key, current->value);
                else
                    printf("declare -x %s\n", current->key);
            }
            current = current->next;
        }
    }
    else
    {
        if ((key_value[0] >= 'a' && key_value[0] <= 'z') || (key_value[0] >= 'A' && key_value[0] <= 'Z'))
        {
            current = *env_cpy1;
            new_node = create_key_value(key_value);
            if (*env_cpy1 == NULL)
                *env_cpy1 = new_node;
            else
            {
                while (current->next)
                    current = current->next;
                current->next = new_node;
            }  
        }
        else
        {
            ft_printf("bash: export: `%s': not a valid identifier\n", key_value);
            return ;
        }     
    }
}


// enlever la ligne _=/usr/bin/env 
// mettre declare -x avant chaque variable
// mettre la valeur de chaque variable entre ""
