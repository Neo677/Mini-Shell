
#include "../include/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	pipex;

	init_pipex(&pipex, argc, argv);
	ft_pid(&pipex, argc, argv, envp);
	ft_check_status(&pipex);
	free_error(&pipex, "", pipex.exit_code);
	return (0);
}
