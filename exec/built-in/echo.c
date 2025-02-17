#include "../include/exec.h"

void    ft_echo(t_command *cmd)
{
    int i;
    int line_break;

    i = 1;
    line_break = 0;
    if (!cmd->arg[1])
    {
        write(1, "\n", 1);
        return ;
    }
    if (cmd->arg[i][0] == '-' && cmd->arg[i][1] == 'n')
    {
        line_break = 1;
        i++;
    }
    while (cmd->arg[i])
    {
        printf("%s", cmd->arg[i]);
        if (cmd->arg[i + 1])
            printf(" ");
        i++;
    }
    if (line_break <= 0)
        printf("\n");
}
