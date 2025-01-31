//                              header


#include "../built-in/built_in.h"

// int main(int argc, char **argv, char **env)
// {
//     // 1- heredoc
//     // 2- checkfile
//     t_pipex pipex;
//     t_command   cmd;
    
//     if (check_dir(&cmd) == -1)
//         return (0);
//     init_var(&pipex);
//     pipex.len = count_cmd(&cmd);
    
// }

void exec(t_command *cmd, t_token *token, char **env)
{
    t_pipex pipex;
    t_buit_in exec;


    // signal(SIGINT, signal_handler);
    // signal(SIGQUIT, signal_handler);

    init_env(&exec, env);

    check_heredoc(&exec, env);

    check_file(token);

    // if (check_builtin(cmd) == 1)
    // {
    //     builtin(cmd, env);
    // }

    // init_var(&pipex);
    // pipex.len = count_cmd(cmd);

    // ft_pid(&pipex, &cmd, env);
    // ft_check_status(&pipex);

    clear_file(pipex.filename_hd);
    // free_error(&pipex, "", pipex.exit_code);

}