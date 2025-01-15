/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:19:37 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/13 13:19:39 by thobenel         ###   ########.fr       */
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
    ft_handle_sig_quit = (CTRL-\)
*/

void ft_set_signal_handler(int sig)
{
    struct sigaction sa_int;
    struct sigaction sa_quit;

    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = SA_RESTART;
}
