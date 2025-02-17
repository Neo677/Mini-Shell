#include "../include/exec.h"

void    ft_unset(t_env **env_cpy, char *key)
{
    delete_node_by_key(env_cpy, key);
}

