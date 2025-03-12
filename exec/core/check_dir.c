#include "../include/exec.h"

int	check_dir_out(t_command *cmd)
{
	t_redirections *dir;

	dir = cmd->redirections;
	while (dir)
	{
		if (dir->type == 3 || dir->type == 4)
			return (1);
		dir = dir->next;
	}
	return (0);
}

int	check_dir_in(t_command *cmd)
{
	t_redirections *dir;

	dir = cmd->redirections;
	while (dir)
	{
		if (dir->type == 2 || dir->type == 5)
			return (1);
		dir = dir->next;
	}
	return (0);
}
