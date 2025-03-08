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

// void signal_handler(int sig)
// {
//     if (sig == SIGINT)
//     {
//         printf("\n");
//         rl_replace_line("", 0);
//         rl_on_new_line();
//         rl_redisplay();
//     }
//     else if (sig == SIGQUIT)
//     {
//         printf("Received SIGQUIT (Ctrl+\\)\n");
//     }
// }
