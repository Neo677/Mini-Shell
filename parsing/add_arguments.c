// header

#include "minishell.h"

/*
                    🚨    🚨    🚨
    for here this is the same goal as add_redirections.c
    but we only need to add a command 
    here we add 2️⃣ arguments to the command :
        the command and the arguments im self (like : ls or cat etc ...)
    so we jsut need to put it in a chain list who name t_command
    for doing that we can :
    1) initialise the cmd->arg if he as no space in memory 
*/

int     ft_add_arguments(t_command *cmd, char *args)
{
    int i;

    if (!cmd || !args)
        return (0);
    i = 0;
    if (!cmd->arg)
    {
        cmd->arg = malloc(sizeof(char *) * 2);
        if (!cmd->arg)
            return (0);
        cmd->arg[0] = ft_strdup(args);
        if (!cmd->arg[0])
            return (free(cmd->arg), 0);
        cmd->arg[1] = NULL;
    }
    else
    {
        while(cmd->arg[i])
            i++;
        cmd->arg = ft_realloc(cmd->arg, sizeof(char *) * (i + 2));
        if (!cmd->arg)
            return (0);
        cmd->arg[i] = ft_strdup(args);
        if (!cmd->arg[i])
            return (0);
        cmd->arg[i + 1] = NULL;
    }
    return (1);
}
