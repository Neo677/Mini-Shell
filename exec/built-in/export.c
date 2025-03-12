/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:31 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/12 10:47:32 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

int	c_var_value(t_buit_in *exec, t_env **env_cpy, char **key_value, int i)
{
	if (split_n_check(exec, key_value, i) == 0)
		return (0);
	if (search_by_key(env_cpy, exec->tab_export[0]) == 0)
	{
		exec->value_export = parse_value(exec->tab_export[1]);
		modify_node_value(env_cpy, exec->tab_export[0], exec->value_export);
		free_tab(exec->tab_export);
		free(exec->value_export);
	}
	else
	{
		if (create_new_node(exec, env_cpy, key_value, i) == 0)
			return (0);
	}
	return (1);
}

int	check_n_c_key(t_buit_in *exec, t_env **env_cpy, char **key_value, int i)
{
	if (check_key_export(key_value[i]) == 1)
	{
		ft_printf_fd(2, "bash: export: `%s': not a valid identifier\n",
			key_value[i]);
		free_env_list(exec->cpy_env_cpy_export);
		exec->status = EXIT_FAILURE;
		return (0);
	}
	key_value[i] = remove_backslash(key_value[i]);
	if (search_by_key(env_cpy, key_value[i]) == 0)
		modify_node_value(env_cpy, key_value[i], NULL);
	else
	{
		if (c_var_key(exec, env_cpy, key_value, i) == 0)
			return (0);
	}
	return (1);
}

int	value_exist(t_buit_in *exec, t_env **env_cpy, char **key_value, int i)
{
	if ((key_value[i][0] >= 'a' && key_value[i][0] <= 'z')
		|| (key_value[i][0] >= 'A' && key_value[i][0] <= 'Z')
		|| key_value[i][0] == '_' || key_value[i][0] == '\\')
	{
		exec->cur_ex = *env_cpy;
		if (check_value(key_value[i]) == 0)
		{
			if (c_var_value(exec, env_cpy, key_value, i) == 0)
				return (0);
		}
		else
		{
			if (check_n_c_key(exec, env_cpy, key_value, i) == 0)
				return (0);
		}
	}
	else
	{
		ft_printf_fd(2, "bash: export: `%s': not a valid identifier\n",
			key_value[i]);
		exec->status = 1;
		free_env_list(exec->cpy_env_cpy_export);
		return (0);
	}
	return (1);
}

int	ft_export(t_buit_in *exec, t_env **env_cpy, char **key_value)
{
	int	i;

	i = 1;
	init_export(exec, env_cpy);
	if (!key_value[1])
	{
		printf_export(exec);
		return (0);
	}
	while (key_value[i])
	{
		if (value_exist(exec, env_cpy, key_value, i) == 0)
			return (1);
		i++;
	}
	free_env_list(exec->cpy_env_cpy_export);
	return (0);
}
