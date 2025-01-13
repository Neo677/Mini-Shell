#include "built_in.h"

char    *cut_path(char *path)
{
    int i;
    char    *new_path;

    i = ft_strlen(path) -1;
    while (path[i] && path[i] != '/')
        i--;
    new_path = malloc(sizeof(char) * i);
    if (!new_path)
        return (NULL);
    new_path[i] = '\0';
    i--;
    while (path[i])
    {
        new_path[i] = path[i];
        i--;
    }
    return (new_path);
}

int    check_and_modify_path(t_env **env, char *path)
{
    if (access(path, F_OK) == 0)
    {
        chdir(path);
        modify_node_value(env, "PWD", path);
    }
    else
        return (-1);
    return (0);
}

// void    cd_source(t_env **env)
// {
//     char *path;

//     path = getcwd(NULL, 0);
//     if (!path)
//         ft_printf(2, "Error\n");
// }

void    cd_back(t_env **env)
{
    char    *path;

    path = getcwd(NULL, 0);
    if (!path)
        perror("Error");
    path = cut_path(path);
    if (check_and_modify_path(env, path) == -1)
        perror("Error");   
}

int check_arg(char *arg)
{
    int i;
    int count;
    int point;

    i = 0;
    count = 0;
    while (arg[i])
    {
        point = 0;
        while (arg[i] && arg[i] == '.')
        {
            point++;
            if (point == 2)
                count++;
            if (point > 2)
                return (-1);
            i++;
        }
        if (!arg[i])
            return (count);
        if (arg[i] && arg[i] != '.' && arg[i] != '/')
            return (-1);
        i++;
    }
    return (count);
}

void    cd_path(t_env **env, char *arg)
{
    int count;

    count = check_arg(arg);
    if (count != -1)
    {
        if (arg[0] == '/' && arg[1] == '/' && arg[2] != '/')
        {
            if (check_and_modify_path(env, "//") == -1)
                perror("Error");
        }
        else if (arg[0] == '/')
        {
            if (check_and_modify_path(env, "/") == -1)
                perror("Error");
        }
        else
        {
            while (count > 0)
            {
                cd_back(env);
                count--;
            }
        }
    }
}


int    ft_cd(t_env **env , char *arg)
{
    int validity_path;
    char    *path_user;


    if (arg)
    {
        if(access(arg, F_OK) == 0)
        {
            validity_path = chdir(arg);
            if (validity_path == -1)
            {
                ft_printf(2, "bash: cd: %s: %s\n", arg, strerror(errno));
                return (0);
            }
            modify_node_value(env, "OLDPWD", print_node_by_key(env, "PWD"));
            modify_node_value(env, "PWD", getcwd(NULL, 0));
            return (1);
        }
        else
            ft_printf(2, "bash: cd: %s: %s\n", arg, strerror(errno));
        return (0);
    }
    else
    {
        path_user = ft_strjoin("/home/", print_node_by_key(env, "USER"));
        chdir(path_user);
        modify_node_value(env, "PWD", path_user);
    }
    return (0);
    
    // if (arg == NULL)
    //     cd_source(env);
    // if (check_arg(arg) >= 0)
    //     cd_path(env, arg);
    
}

// chdir
// int chdir(const char *path);
// Description : Change le répertoire de travail courant du programme.

// Afficher un dollars pour / et //
// Trouver comment afficher // au lieu de /