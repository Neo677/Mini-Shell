#include "../include/exec.h"

int	search_node_and_value(t_env **env, char *key, char *value)
{
	t_env	*current;

	current = env[0];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0 && ft_strcmp(current->value,
				value) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

int	search_by_key(t_env **env, char *key)
{
	t_env	*current;

	current = env[0];
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

char	*print_node_by_key(t_env **env, char *key)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}
