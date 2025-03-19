/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 18:32:43 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/19 22:52:04 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	signal_handler_exec(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit (core dumped)\n");
	}
}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit (core dumped)\n");
	}
}

void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
		printf("Quit (core dumped)\n");
	}
}

void	signal_handler3(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		printf("\n");
		close(STDIN_FILENO);
	}
}

void	signal_handler4(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
	}
	else if (sig == SIGQUIT)
	{
		g_signal = 131;
	}
}
