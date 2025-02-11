#include "built_in.h"

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
                ft_printf_fd(2, "bash: cd: %s: %s\n", arg, strerror(errno));
                return (0);
            }
            modify_node_value(env, "OLDPWD", print_node_by_key(env, "PWD"));
            modify_node_value(env, "PWD", getcwd(NULL, 0));
            return (1);
        }
        else
            ft_printf_fd(2, "bash: cd: %s: %s\n", arg, strerror(errno));
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