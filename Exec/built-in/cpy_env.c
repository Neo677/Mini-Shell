#include "built_in.h"

int ft_strlen_c(char *str, int i, char c)
{
    int len;

    len = 0;
    while (str[i] && str[i] != c)
    {
        i++;
        len++;
    }
    return (len);
}

int check_value(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '=')
            return (0);
        i++;
    }
    return (1);
}

// char    **split_in_two(char *str, char c)
// {
//     int i;
//     int j;
//     char    **tab;

//     tab = malloc(sizeof(char *) * 2 + 1);
//     if (!tab)
//         return (NULL);
//     i = 0;
//     tab[0] = malloc(sizeof(char) * ft_strlen_c(str, i, c) + 1);
//     if (!tab[0])
//         return (NULL);
//     j = 0;
//     while (str[i] && str[i] != c)
//         tab[0][j++] = str[i++];
//     tab[0][j] = '\0';
//     i++;
//     tab[1] = malloc(sizeof(char) * ft_strlen_c(str, i, '\0') + 1);
//     if (!tab[1])
//         return (NULL);
//     j = 0;
//     if (!str[i])
//     {
//         tab[1][j] = '\0';
//         tab[2] = NULL;
//         return (tab);
//     }
//     while (str[i])
//         tab[1][j++] = str[i++];
//     tab[1][j] = '\0';
//     // tab[2] = NULL;
//     return (tab);
// }

char    **split_in_two(char *str, char c)
{
    int i;
    int j;
    int len;
    char    **tab;

    len = 2;
    tab = malloc(sizeof(char *) * len + 1);
    if (!tab)
        return (NULL);
    i = 0;
    tab[0] = malloc(sizeof(char) * ft_strlen_c(str, i, c) + 1);
    if (!tab[0])
        return (NULL);
    j = 0;
    while (str[i] && str[i] != c)
        tab[0][j++] = str[i++];
    tab[0][j] = '\0';
    i++;
    tab[1] = malloc(sizeof(char) * ft_strlen_c(str, i, '\0') + 1);
    if (!tab[1])
        return (NULL);
    j = 0;
    while (str[i])
        tab[1][j++] = str[i++];
    tab[1][j] = '\0';
    return (tab);
}

// t_env    *create_key_value(char *env)
// {
//     t_env   *node;
//     char **tab;

//     tab = split_in_two(env, '=');
//     if (!tab)
//         return (NULL);
//     node = create_node(tab[0], tab[1]);
//     free (tab[0]);
//     free (tab[1]);
//     free (tab);
//     return (node);
// }

t_env    *create_key_value(char *env)
{
    t_env   *node;
    char **tab;

    if (check_value(env) == 0)
    {
        tab = split_in_two(env, '=');
        if (!tab)
            return (NULL);
        node = create_node(tab[0], tab[1]);
        free (tab[0]);
        free (tab[1]);
        free (tab);
    }
    else
    {
        node = create_node(env, NULL);
        free (env);
    }
    return (node);
}

void    copy_env(char **env, t_env **env_cpy)
{
    t_env   *new_node;
    t_env   *current;
    int i;

    i = 0;
    while (env[i])
    {
        new_node = create_key_value(env[i]);
        if (!new_node)
            return ;
        if (env_cpy[0] == NULL)
            env_cpy[0] = new_node;
        else
        {
            current = env_cpy[0];
            while (current->next != NULL)
                current = current->next;
            current->next = new_node;
        }
        i++;
    }
}
