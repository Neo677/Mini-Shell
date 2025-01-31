

#include "../built-in/built_in.h"

// void	init_pipex(t_pipex *pipex, t_command *cmd)
// {
// 	init_var(pipex);
// 	pipex->infile = open(cmd->redirections->file, O_RDONLY, 0644);
// 	if (pipex->infile < 0)
// 	{
// 		ft_printf_fd(2, "bash: ");
// 		perror(cmd->redirections->file);
// 		pipex->infile = open("temp_null", O_RDONLY | O_CREAT | O_TRUNC, 0644);
// 		pipex->error = 1;
// 	}
// 	pipex->outfile = open(cmd->redirections->file, O_TRUNC | O_CREAT | O_WRONLY, 0644);
// 	if (pipex->outfile < 0)
// 	{
// 		ft_printf_fd(2, "bash: ");
// 		perror(cmd->redirections->file);
// 		pipex->outfile = open("temp_null2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 		pipex->error_outfile = 1;
// 	}
// 	if (pipe(pipex->pipefd) == -1)
// 		free_error(pipex, "Error : pipefd", 0);
// }

void    init_env(t_buit_in *exec, char **env)
{
    init_var_builtin(exec);
    copy_env(env, &exec->env_cpy);
    modify_node_value(&exec->env_cpy, "_", "/usr/bin/env");
}