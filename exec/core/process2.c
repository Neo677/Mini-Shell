#include "../include/exec.h"

int	no_built_in(t_pipex *pipex, t_buit_in *exec, char **env, t_command *current)
{
	pipex->pid = fork();
	if (pipex->pid < 0)
		return (perror("fork"), 0);
	if (pipex->pid == 0)
	{
		signal(SIGQUIT, signal_handler);
		redir_input(exec, current, pipex);
		redir_output(exec, current, pipex);
		if (check_file2(exec, current) == 1)
			exit(1);
		execute_cmd(exec, pipex, current->arg, env);
	}
	wait(&pipex->status);
	if (WIFEXITED(pipex->status))
		return (exec->status = WEXITSTATUS(pipex->status));
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	return (0);
}
