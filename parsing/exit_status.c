

#include "minishell.h"

int get_last_exit_status(void)
{
    static int last_status;
    return last_status;
}