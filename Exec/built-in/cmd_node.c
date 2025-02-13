#include "built_in.h"

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
    current = env_cpy[0]; // copie du poiteur vers le debut de notre liste chainee pour pouvoir s'y deplacer
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0) // recherche de la KEY a laquelle on veut modifier la valeur
        {
            if (current->value)
                free(current->value); // libere l'ancienne valeur
            if (new_value)
            {
                current->value = ft_strdup(new_value); // alloue de la memoire et copie la nouvelle valeur
                if (!current->value)
                    return (0);
            }
            else
                current->value = NULL;
            return (1);
        }
        current = current->next; // sinon passe au noeud suivant
    }
    return (0);
}

int    delete_node_by_key(t_env **env_cpy, char *key)
{
    t_env *current;
    t_env *previous;

    current = *env_cpy; // copie du poiteur vers le debut de notre liste chainee pour pouvoir s'y deplacer
    previous = NULL;
    while (current)
    {
        if (ft_strcmp(current->key, key) == 0) // compare si la KEY du noeud actuel est la meme que celle que l'on veut supprimer
        {
            if (previous == NULL) // previous est le noeud précédent, si il est egal a NULL cela signifie que l'on traite le premier noeud
                *env_cpy = current->next; // donc ici on fait pointer le debut de notre liste chainee vers le deuxieme noeud
            else
                previous->next = current->next; // Si ce n'est pas le premier noeud fait pointer le noeud precedent vers le noeud suivant de celui que l'on souhaite supprimer
            free(current->key);
            free(current->value);
            free(current); // liberation du noeud et de ses valeurs
            return (1);
        }
        previous = current; // sinon passer au noeud suivant
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
        {
            return (current->value);
        }
            
        current = current->next;
    }
    return (NULL);
}
