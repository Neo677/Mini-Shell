/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:19:37 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/18 03:39:07 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// not use yet

/*
    here :
    1) we can see thaht i first use rl_on_new_line for say to our shell is ready for a new ligne.
    2) rl_replace_line like this name said is replace the actual line
    3) rl_redisplay updates the prompt screen ($>)

*/

// ft_handle_sig_int = (CTRL-C)

void ft_handle_sig_int(int sig)
{
    (void)sig;
    printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0); // LINUX
    rl_redisplay();
}

void ft_handle_sig_quit(int sig)
{
    (void)sig;  // ignore the signal
}

/*  
    Here we need to config the handler for the signal
    on the top i do 2 fonction :
    ft_handle_sig_quit = (CTRL-\)
*/

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
