#include "../include/exec.h"

void	ft_env(t_env **env_cpy)
{
	t_env	*current;

	current = *env_cpy;
	while (current)
	{
		if (current->val != 1)
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
