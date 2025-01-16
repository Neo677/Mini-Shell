

#include "../include/pipex.h"

int main(int argc, char **argv, char **env)
{
    // 1- heredoc
    // 2- checkfile
    t_pipex pipex;
    t_command   cmd;
    
    if (check_dir(&cmd) == -1)
        return (0);
    init_var(&pipex);
    pipex.len = count_cmd(&cmd);
    
}
