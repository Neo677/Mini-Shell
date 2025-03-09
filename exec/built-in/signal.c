#include "../include/exec.h"

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
	}
}

void	signal_handler2(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		printf("Quit (core dumped)\n");
	}
}
