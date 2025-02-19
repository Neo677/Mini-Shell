#include "../include/exec.h"

// void    ft_pwd(t_env **env, int cd)
// {
//     char    *pwd;

//     if (search_node_and_value(env, "PWD", "//") == 0 || search_node_and_value(env, "PWD", "/") == 0)
//     {
//         if (search_node_and_value(env, "PWD", "//") == 0)
//             printf("/");
//         printf("/\n");
//         return ;
//     }
//     if (cd == 1)
//     {
//         pwd = getcwd(NULL, 0);
//         if (!pwd)
//             ft_printf_fd(2, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
//         else
//         {
//             printf("%s\n", pwd);
//             if (access(print_node_by_key(env, "OLDPWD"), F_OK) != 0)
//                 ft_printf_fd(2, "bash: %s: %s\n", print_node_by_key(env, "OLDPWD"), strerror(errno));
//             free(pwd);
//         }
//         cd = 0;
//     }
//     else
//     {
//         printf("%s\n", print_node_by_key(env, "PWD"));
//         if (access(print_node_by_key(env, "OLDPWD"), F_OK) != 0)
//             ft_printf_fd(2, "bash: %s: %s\n", print_node_by_key(env, "OLDPWD"), strerror(errno));
//     }
// }

int pwd_with_cd(t_env **env, int cd)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
    if (!pwd)
        ft_printf_fd(2, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory");
    else
    {
        printf("%s\n", pwd);
        if (access(print_node_by_key(env, "OLDPWD"), F_OK) != 0)
            ft_printf_fd(2, "bash: %s: %s\n", print_node_by_key(env, "OLDPWD"), strerror(errno));
        free(pwd);
    }
    cd = 0;
    return (cd);
}

void    ft_pwd(t_env **env, int cd)
{
    if (search_node_and_value(env, "PWD", "//") == 0 || search_node_and_value(env, "PWD", "/") == 0)
    {
        if (search_node_and_value(env, "PWD", "//") == 0)
            printf("/");
        printf("/\n");
        return ;
    }
    if (cd == 1)
        cd = pwd_with_cd(env, cd);
    else
    {
        printf("%s\n", print_node_by_key(env, "PWD"));
        if (access(print_node_by_key(env, "OLDPWD"), F_OK) != 0)
            ft_printf_fd(2, "bash: %s: %s\n", print_node_by_key(env, "OLDPWD"), strerror(errno));
    }
}
// mettre a jour la variable d'environnement OLDPWD
// Affichage de OLDPWD = bash: /PATH: Is a directory
