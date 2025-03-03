#include "../include/exec.h"

void	ft_unset(t_buit_in *exec, t_env **env_cpy, char *key)
{
	if (!key)
	{
		exec->status = 0;
		return ;
	}
	delete_node_by_key(env_cpy, key);
}
