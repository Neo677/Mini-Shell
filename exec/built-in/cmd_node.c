#include "../include/exec.h"

t_env    *create_node(char *key, char *value)
{
    t_env *node;

    node = malloc(sizeof(t_env));
    if (!node)
        return (NULL);
    node->key = ft_strdup(key);
    if (value)
    {
        node->value = ft_strdup(value);
        node->val = 0;
    }
    else
    {
        node->value = NULL;
        node->val = 1;
    }
    node->next = NULL;
    return (node);
}

int    modify_node_value(t_env **env_cpy, char *key, char *new_value)
{
    t_env *current;
    current = env_cpy[0];
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (current->value)
                free(current->value);
            if (new_value)
            {
                current->value = ft_strdup(new_value);
                if (!current->value)
                    return (0);
            }
            else
                current->value = NULL;
            return (1);
        }
        current = current->next;
    }
    return (0);
}

int    delete_node_by_key(t_env **env_cpy, char *key)
{
    t_env *current;
    t_env *previous;

    current = *env_cpy;
    previous = NULL;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            if (previous == NULL)
                *env_cpy = current->next;
            else
                previous->next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return (1);
        }
        previous = current;
        current = current->next;
    }
    return (0);
}

int search_node_and_value(t_env **env, char *key, char *value)
{
    t_env *current;

    current = env[0];
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0 && ft_strcmp(current->value, value) == 0)
            return (0);
        current = current->next;
    }
    return (1);
}

int search_by_key(t_env **env, char *key)
{
    t_env *current;

    current = env[0];
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return (0);
        current = current->next;
    }
    return (1);
}

char    *print_node_by_key(t_env **env, char *key)
{
    t_env   *current;

    current = *env;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0)
            return (current->value);
        current = current->next;
    }
    return (NULL);
}
