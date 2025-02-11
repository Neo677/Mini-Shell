

#include "../built-in/built_in.h"

void	init_var(t_pipex *pipex)
{
	pipex->infile = dup(STDIN_FILENO);
	pipex->outfile = dup(STDOUT_FILENO);
	pipex->pipefd[0] = 0;
	pipex->pipefd[1] = 0;
	pipex->len = 0;
	pipex->pid = 0;
	pipex->i = 0;
	pipex->stdin_fd = 0;
	pipex->status = 0;
	pipex->exit_code = 0;
	pipex->error = 0;
	pipex->error_outfile = 0;
	pipex->cmd = NULL;
	pipex->paths = NULL;
	pipex->path = NULL;
	pipex->paths_cmd = NULL;
	pipex->path_cmd = NULL;
	pipex->in = NULL;
	pipex->out = NULL;
	pipex->filename_hd = NULL;
}
