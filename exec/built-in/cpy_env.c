#include "../include/exec.h"

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

//     tab = malloc(sizeof(char *) * 3);
//     if (!tab)
//         return (NULL);
//     tab[0] = NULL;
//     tab[1] = NULL;
//     tab[2] = NULL;
//     tab[0] = malloc(sizeof(char) * ft_strlen_c(str, 0, c) + 1);
//     if (!tab[0])
//     {
//         free(tab);
//         return (NULL);
//     }
//     i = 0;
//     j = 0;
//     while (str[i] && str[i] != c)
//         tab[0][j++] = str[i++];
//     tab[0][j] = '\0';
//     i++;
//     tab[1] = malloc(sizeof(char) * ft_strlen_c(str, i, '\0') + 1);
//     if (!tab[1])
//     {
//         free_tab(tab);
//         return (NULL);
//     }
//     j = 0;
//     while (str[i])
//         tab[1][j++] = str[i++];
//     tab[1][j] = '\0';
//     return (tab);
// }

char    **init_split_in_two(char *str, char c)
{
    char **tab;

    tab = malloc(sizeof(char *) * 3);
    if (!tab)
        return (NULL);
    tab[0] = NULL;
    tab[1] = NULL;
    tab[2] = NULL;
    tab[0] = malloc(sizeof(char) * ft_strlen_c(str, 0, c) + 1);
    if (!tab[0])
    {
        free(tab);
        return (NULL);
    }
    return (tab);
}

char    **split_in_two(char *str, char c)
{
    int i;
    int j;
    char    **tab;

    tab = init_split_in_two(str, c);
    i = 0;
    j = 0;
    while (str[i] && str[i] != c)
        tab[0][j++] = str[i++];
    tab[0][j] = '\0';
    i++;
    tab[1] = malloc(sizeof(char) * ft_strlen_c(str, i, '\0') + 1);
    if (!tab[1])
    {
        free_tab(tab);
        return (NULL);
    }
    j = 0;
    while (str[i])
        tab[1][j++] = str[i++];
    tab[1][j] = '\0';
    return (tab);
}

char *parse_value(char *input)
{
    char *result;
    int i;
    int j;
    char quote;

    i = 0;
    j = 0;
    quote = 0;
    result  = malloc(ft_strlen(input) + 1);
    if (!result)
        return (NULL);
    while (input[i])
    {
        if (!quote && (input[i] == '\'' || input[i] == '\"'))
            quote = input[i];
        else if (quote && input[i] == quote)
            quote = 0;
        else
            result[j++] = input[i];
        i++;
    }
    result[j] = '\0';
    return (result);
}

// t_env    *create_key_value(char *env)
// {
//     t_env   *node;
//     char **tab;
//     char *tmp;

//     if (check_value(env) == 0)
//     {
//         tab = split_in_two(env, '=');
//         if (!tab)
//             return (NULL);
//         tmp = tab[1];
//         tab[1] = parse_value(tab[1]);
//         free(tmp);
//         if (!tab[1])
//         {
//             free_tab(tab);
//             return (NULL);
//         }
//         node = create_node(tab[0], tab[1]);
//         if (!node)
//         {
//             free_tab(tab);
//             return (NULL);
//         }
//         free_tab(tab);  
//     }
//     else
//         node = create_node(env, NULL);
//     return (node);
// }

char    **init_create_key_value(char *env)
{
    char    **tab;
    char    *tmp;

    tab = split_in_two(env, '=');
    if (!tab)
        return (NULL);
    tmp = tab[1];
    tab[1] = parse_value(tab[1]);
    free(tmp);
    if (!tab[1])
    {
        free_tab(tab);
        return (NULL);
    }
    return (tab);
}

t_env    *create_key_value(char *env)
{
    t_env   *node;
    char **tab;

    if (check_value(env) == 0)
    {
        tab = init_create_key_value(env);
        node = create_node(tab[0], tab[1]);
        if (!node)
        {
            free_tab(tab);
            return (NULL);
        }
        free_tab(tab);  
    }
    else
        node = create_node(env, NULL);
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
