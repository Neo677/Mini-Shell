// header

#include "minishell.h"

t_command *ft_create_command(void)
{
    t_command *cmd;

    cmd = malloc(sizeof(t_command));
    if (!cmd)
        error_exit("Bad processing of create a command");
    cmd->arg = NULL;
    cmd->redirections = NULL;
    cmd->p_pipe = 0;
    cmd->next = NULL;
    return (cmd);
}