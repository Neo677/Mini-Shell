
#include "built_in.h"

void signal_handler(int sig)
{
    if (sig == SIGINT)
    {
        printf("\n");
        rl_replace_line("", 0);
        rl_on_new_line();
        // rl_redisplay();

    }
    else if (sig == SIGQUIT)
    {
        printf("Received SIGQUIT (Ctrl+\\)\n");
        // exit (0);
    }
}

// void signal_handler(int sig)
// {
//     if (sig == SIGINT)
//     {
//         /* On écrit un retour à la ligne pour quitter la ligne en cours */
//         write(STDOUT_FILENO, "\n", 1);
//         /* On efface la ligne en cours dans readline */
//         rl_replace_line("", 0);
//         /* On indique à readline que nous sommes sur une nouvelle ligne */
//         rl_on_new_line();
//         /* On redessine le prompt */
//         rl_redisplay();
//     }
//     else if (sig == SIGQUIT)
//     {
//         /* En mode interactif, on ignore SIGQUIT (CTRL-\) */
//         printf("Received SIGQUIT (Ctrl+\\)\n");
//     }
// }




// void ft_handle_sig_int(int sig)
// {
//     (void)sig;
//     printf("\n");
//     rl_on_new_line();
//     rl_replace_line("", 0); // LINUX
//     rl_redisplay();
// }

// void ft_handle_sig_quit(int sig)
// {
//     (void)sig;  // ignore the signal
// }

// /*  
//     Here we need to config the handler for the signal
//     on the top i do 2 fonction :
//     ft_handle_sig_quit = (CTRL-\)
// */

// void ft_set_signal_handler(void)
// {
//     struct sigaction sa_int;
//     struct sigaction sa_quit;

//     // gestion de SIGQUIT (CTRL-C)
//     sigemptyset(&sa_int.sa_mask);
//     sa_int.sa_handler = ft_handle_sig_int;
//     sa_int.sa_flags = SA_RESTART;
//     sigaction(SIGINT, &sa_int, NULL);

//     // gestion de SIGQUIT (CTRL-D)
//     sigemptyset(&sa_quit.sa_mask);
//     sa_quit.sa_handler = SIG_IGN;
//     sa_quit.sa_flags = 0;
//     sigaction(SIGQUIT, &sa_quit, NULL);
// }