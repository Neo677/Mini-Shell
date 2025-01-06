// header

#include "minishell.h"

/*
    here :
    1) we can see thaht i first use rl_on_new_line for say to our shell is ready for a new ligne.
    2) rl_replace_line like this name said is replace the actual line
    3) rl_redisplay updates the prompt screen ($>)

*/

void ft_handle_sig_int(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void ft_handle_sig_quit(int sig)
{
    (void)sig;  // ignore the signal
}

/*  
    Here we need to config the handler for the signal
    on the top i do 2 fonction :
    ft_handle_sig_int = (CTRL-C)
    ft_handle_sig_quit = (CTRL-\)


*/

void ft_set_signal_handler(int sig)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
    sa_int.sa_handler = ft_handle_sig_int;
    sigaction(SIGINT, &sa_int, NULL);
    
    sigemptyset(&sa_quit.sa_mask);
    sa_quit.sa_flags = SA_RESTART;
    sa_quit.sa_handler = ft_handle_sig_quit;
    sigaction(SIGQUIT, &sa_quit, NULL);
}
