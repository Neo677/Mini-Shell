

#include "../include/pipex.h"

void	exec(t_command *cmd, t_token *token, char **env)
{
    // (void)token;
    t_pipex	pipex;
    t_built_in   exec;
    (void)cmd;
    // (void)env;
    // Signal
    // signal(SIGINT, signal_handler);
    // signal(SIGQUIT, signal_handler);
    
    // 0 copy env
    init_env(&exec, env);

    // 1 open heredoc
    check_heredoc(token, &pipex);

    // 2 check file
    check_file(token);

    // 3 check built in
    // if (check_builtin(cmd) == 1)
    //     builtin(cmd, env);

    // 4 exec cmd en fonction des redirections
	// init_var(&pipex);
	// pipex.len = count_cmd(cmd);

	// ft_pid(&pipex, &cmd, env);
	// ft_check_status(&pipex);
    
    // 5 Clear and free
    clear_file(pipex.filename_hd);
	// free_error(&pipex, "", pipex.exit_code);

}

