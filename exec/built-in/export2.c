/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:35 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:47:36 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	init_export(t_buit_in *exec, t_env **env_cpy)
{
	exec->cur_ex = NULL;
	exec->new_node_export = NULL;
	exec->env_cpy_export = NULL;
	exec->cpy_env_cpy_export = NULL;
	exec->tab_export = NULL;
	exec->value_export = NULL;
	exec->env_cpy_export = export_cpy(env_cpy, &exec->cpy_env_cpy_export);
}

void	printf_export(t_buit_in *exec)
{
	sort_list(exec->env_cpy_export);
	exec->cur_ex = *exec->env_cpy_export;
	while (exec->cur_ex)
	{
		if ((exec->cur_ex->key[0] >= 'a' && exec->cur_ex->key[0] <= 'z')
			|| (exec->cur_ex->key[0] >= 'A' && exec->cur_ex->key[0] <= 'Z')
			|| exec->cur_ex->key[0] == '_' || exec->cur_ex->key[0] == '\\')
		{
			if (exec->cur_ex->value)
			{
				if (check_b_n(exec->cur_ex->value) == 1)
					printf("declare -x %s=$\'%s\'\n", exec->cur_ex->key,
						replace_b_n(exec->cur_ex->value));
				else
					printf("declare -x %s=\"%s\"\n", exec->cur_ex->key,
						exec->cur_ex->value);
			}
			else
				printf("declare -x %s\n", exec->cur_ex->key);
		}
		exec->cur_ex = exec->cur_ex->next;
	}
	free_env_list(exec->cpy_env_cpy_export);
}

int	split_n_check(t_buit_in *exec, char **key_value, int i)
{
	char	*temp;

	exec->tab_export = split_in_two(key_value[i], '=');
	if (!exec->tab_export)
	{
		free_env_list(exec->cpy_env_cpy_export);
		return (0);
	}
	if (check_key_export(exec->tab_export[0]) == 1)
	{
		ft_printf_fd(2, "bash: export: `%s': not a valid identifier\n",
			key_value[i]);
		free_tab(exec->tab_export);
		free_env_list(exec->cpy_env_cpy_export);
		exec->status = EXIT_FAILURE;
		return (0);
	}
	temp = exec->tab_export[0];
	exec->tab_export[0] = remove_backslash(exec->tab_export[0]);
	free(temp);
	return (1);
}

int	create_new_node(t_buit_in *exec, t_env **env_cpy, char **key_value, int i)
{
	char	*temp;

	temp = remove_backslash(key_value[i]);
	exec->new_node_export = create_key_value(temp);
	free(temp);
	if (!exec->new_node_export)
	{
		free_tab(exec->tab_export);
		free_env_list(exec->cpy_env_cpy_export);
		return (0);
	}
	if (env_cpy == NULL)
		*env_cpy = exec->new_node_export;
	else
	{
		while (exec->cur_ex->next)
			exec->cur_ex = exec->cur_ex->next;
		exec->cur_ex->next = exec->new_node_export;
	}
	free_tab(exec->tab_export);
	return (1);
}

int	c_var_key(t_buit_in *exec, t_env **env_cpy, char **key_value, int i)
{
	exec->new_node_export = create_key_value(key_value[i]);
	if (!exec->new_node_export)
	{
		free_tab(exec->tab_export);
		free_env_list(exec->cpy_env_cpy_export);
		return (0);
	}
	if (env_cpy == NULL)
		*env_cpy = exec->new_node_export;
	else
	{
		while (exec->cur_ex->next)
			exec->cur_ex = exec->cur_ex->next;
		exec->cur_ex->next = exec->new_node_export;
	}
	return (1);
}
