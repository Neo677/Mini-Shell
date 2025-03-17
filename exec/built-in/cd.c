/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:46:57 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/17 07:57:59 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

char	*modify_pwd_with_arg(char *path, char *arg)
{
	char	*new_path;
	char	*result;

	if (!arg || !path)
		return (NULL);
	new_path = ft_strjoin(path, "/");
	if (!new_path)
		return (NULL);
	result = ft_strjoin(new_path, arg);
	free(new_path);
	return (result);
}

int	modify_path(char *arg, t_env **env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_printf_fd(2, CD_ERR CD_ERR2);
		path = modify_pwd_with_arg(print_node_by_key(env, "PWD"), arg);
		if (!path)
			return (0);
	}
	modify_node_value(env, "PWD", path);
	free(path);
	return (1);
}

int	cd_less(t_buit_in *exec, t_env **env)
{
	char	*temp;
	char	*oldpwd;

	oldpwd = ft_strdup(print_node_by_key(env, "OLDPWD"));
	if (!oldpwd)
	{
		ft_printf_fd(2, "bash: cd: OLDPWD not set\n");
		exec->status = 1;
		return (0);
	}
	temp = ft_strdup(print_node_by_key(env, "PWD"));
	if (chdir(oldpwd) == -1)
	{
		ft_printf_fd(2, "bash: cd: %s: %s\n", oldpwd, strerror(errno));
		exec->status = 1;
		free(oldpwd);
		return (0);
	}
	modify_node_value(env, "PWD", oldpwd);
	modify_node_value(env, "OLDPWD", temp);
	printf("%s\n", oldpwd);
	free(oldpwd);
	free(temp);
	return (0);
}

int	arg_cd(t_buit_in *exec, char *arg, t_env **env)
{
	int		validity_path;

	if (access(arg, F_OK) == 0)
	{
		validity_path = chdir(arg);
		if (validity_path == -1)
			return (ft_printf_fd(2, "bash: cd: %s: %s\n", arg, strerror(errno)),
				0);
		modify_node_value(env, "OLDPWD", print_node_by_key(env, "PWD"));
		return (modify_path(arg, env));
	}
	else
	{
		if (ft_strcmp(arg, "-") == 0)
		{
			cd_less(exec, env);
			return (0);
		}
		ft_printf_fd(2, "bash: cd: %s: %s\n", arg, strerror(errno));
		exec->status = 1;
	}
	return (0);
}

int	ft_cd(t_buit_in *exec, t_env **env, char **arg)
{
	char	*path;

	if (arg[1])
	{
		if (arg[2])
		{
			ft_printf_fd(2, "bash: cd: too many arguments\n");
			exec->status = 1;
			return (0);
		}
		return (arg_cd(exec, arg[1], env));
	}
	path = print_node_by_key(env, "HOME");
	if (!path)
	{
		ft_printf_fd(2, "bash: cd: HOME not set\n");
		exec->status = 1;
		return (0);
	}
	if (chdir(path) == -1)
	{
		ft_printf_fd(2, "bash: cd: %s: %s\n", path, strerror(errno));
		return (0);
	}
	return (modify_node_value(env, "PWD", path), 1);
}
