

#include "../include/pipex.h"

void    init_env(t_built_in *exec, char **env)
{
    init_var_builtin(exec);
    copy_env(env, &exec->env_cpy);
    modify_node_value(&exec->env_cpy, "_", "/usr/bin/env");
}
