#include "../include/exec.h"

char	*modify_pwd_with_arg(char *path, char *arg)
{
	char	*new_path;
	int		i;
	int		j;

	if (!arg)
		return (path);
	new_path = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(arg) + 1));
	if (!new_path)
		return (path);
	i = 0;
	j = 0;
	while (path[i])
	{
		new_path[j++] = path[i++];
	}
	i = 0;
	new_path[j++] = '/';
	while (arg[i])
	{
		new_path[j++] = arg[i++];
	}
	new_path[j] = '\0';
	return (new_path);
}

int	modify_path(char *arg, t_env **env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_printf_fd(2, CD_ERR CD_ERR2);
		path = modify_pwd_with_arg(print_node_by_key(env, "PWD"), arg);
		modify_node_value(env, "PWD", path);
		free(path);
		return (0);
	}
	modify_node_value(env, "PWD", path);
	free(path);
	return (1);
}

int	arg_cd(t_buit_in *exec, char *arg, t_env **env)
{
	int	validity_path;

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
		ft_printf_fd(2, "bash: cd: %s: %s\n", arg, strerror(errno));
		exec->status = 1;
	}
	return (0);
}

int	ft_cd(t_buit_in *exec, t_env **env, char **arg)
{
	char	*path_user;

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
	else
	{
		path_user = ft_strjoin("/home/", print_node_by_key(env, "USER"));
		if (!path_user)
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
