#include "../include/exec.h"

int    ft_cd(t_env **env , char *arg)
{
    int validity_path;
    char    *path_user;
    char    *path;

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
            path = getcwd(NULL, 0);
            if (!path)
            {
                ft_printf_fd(2, "bash: cd: %s: %s\n", arg, strerror(errno));
                return (0);
            }
            modify_node_value(env, "PWD", path);
            free(path);
            return (1);
        }
        else
            ft_printf_fd(2, "bash: cd: %s: %s\n", arg, strerror(errno));
        return (0);
    }
    else
    {
        path_user = ft_strjoin("/home/", print_node_by_key(env, "USER"));
        if(!path_user)
        {
            ft_printf_fd(2, "bash: cd: %s: %s\n", arg, strerror(errno));
            return (0);
        }
        chdir(path_user);
        modify_node_value(env, "PWD", path_user);
        free(path_user);
    }
    return (0);
}
