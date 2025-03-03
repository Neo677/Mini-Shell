#include "../include/exec.h"

int	pwd_with_cd(t_env **env, int cd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		ft_printf_fd(2, "%s\n", print_node_by_key(env, "PWD"));
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	cd = 0;
	return (cd);
}

void	ft_pwd(t_env **env, int cd)
{
	if (search_node_and_value(env, "PWD", "//") == 0
		|| search_node_and_value(env, "PWD", "/") == 0)
	{
		if (search_node_and_value(env, "PWD", "//") == 0)
			printf("/");
		printf("/\n");
		return ;
	}
	if (cd == 1)
		cd = pwd_with_cd(env, cd);
	else
	{
		printf("%s\n", print_node_by_key(env, "PWD"));
		if (access(print_node_by_key(env, "OLDPWD"), F_OK) != 0)
			ft_printf_fd(2, "bash: %s: %s\n", print_node_by_key(env, "OLDPWD"),
				strerror(errno));
	}
}
