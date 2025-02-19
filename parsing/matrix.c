#include "minishell.h"

#define WIDTH 80
#define HEIGHT 24
#define DELAY 80000

static void	clear_screen(void)
{
	printf("\033[2J");
	printf("\033[H");
}

static void	draw_matrix(int cols[])
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		if (rand() % 10 < 3)
			cols[x] = rand() % HEIGHT;
		y = 0;
		while (y < HEIGHT)
		{
			if (y == cols[x])
				printf("\033[%d;%dH\033[32m%c\033[0m", y, x,
					(rand() % 2) + '0');
			y++;
		}
		x++;
	}
}

static void	display_message(void)
{
	int			message_start;
	int			message_width;
	int			i;
	const char	*message[] = {
		"#########################################",
		"#         WELCOME TO MINISHELL          #",
		"#              BUILT BY                 #",
		"#         Dpascal AND Thobenel          #",
		"#########################################",
		NULL
	};

	message_start = (HEIGHT - 5) / 2;
	message_width = 40;
	i = 0;
	while (message[i] != NULL)
	{
		printf("\033[%d;%dH\033[33m%s\033[0m", message_start + i,
			(WIDTH - message_width) / 2, message[i]);
		i++;
	}
}

void	matrix_effect(void)
{
	int	cols[WIDTH] = {0};

	srand(time(NULL));
	while (1)
	{
		clear_screen();
		draw_matrix(cols);
		display_message();
		fflush(stdout);
		usleep(DELAY);
		if (rand() % 50 == 0)
			break ;
	}
	clear_screen();
}

void	ft_introw(void)
{
	int			i;
	const char	*intro[] = {
		"Enter command below for tokenize that shit 🧑‍🍳",
		"type 'exit' to quit this shell, dude",
		NULL
	};

	matrix_effect();
	i = 0;
	while (intro[i])
	{
		printf("%s\n", intro[i]);
		i++;
	}
}