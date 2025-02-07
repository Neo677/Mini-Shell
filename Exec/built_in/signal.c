#include "built_in.h"

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (sig == SIGQUIT)
    {
        printf("Received SIGQUIT (Ctrl+\\)\n");
    }
}