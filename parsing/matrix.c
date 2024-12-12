/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:58 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:00 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_intro(void)
{
    int i;
    const char *intro[] = {
        "#########################################",
        "#         WELCOME TO MINISHELL          #",
        "#  (Build)Dpascal AND Thobenel(parsing) #",
        "#        LEXER PART BY thobenel         #",
        "#########################################",
        "Enter command below for tokenize that shit 🧑‍🍳",
        "type 'exit' to quit this shell, dude",
        NULL
    };
    matrix_effect(); // Lancer l'effet Matrix si activé
    i = 0;
    while (intro[i])
    {
        ft_printf("%s\n", intro[i]);
        i++;
    }
        
}



void clear_screen()
{
    printf("\033[2J"); // Efface l'écran
    printf("\033[H");  // Replace le curseur en haut à gauche
}

static void draw_matrix(int cols[])
{
    int x;
    int y;
    x = 0;
    while (x < WIDTH)
    {
        if (rand() % 10 < 3) // 30% de chance de rafraîchir une colonne
            cols[x] = rand() % HEIGHT;
        y = 0;
        while (y < HEIGHT)
        {
            if (y == cols[x])
                printf("\033[%d;%dH\033[32m%c\033[0m", y, x, (rand() % 2) + '0'); // Affiche 0 ou 1
            y++;
        }
        x++;
    }
}

static void     display_message()
{
    int message_start;
    int message_width;
    int i;
    const char *message[] = {
        "#########################################",
        "#         WELCOME TO MINISHELL          #",
        "#         BUILT-IN BY Dpascal           #",
        "#        LEXER PART BY thobenel         #",
        "#########################################",
        NULL
    };
    message_start = (HEIGHT - 5) / 2; // 5 lignes de message
    message_width = 40;              // Largeur du message
    i = 0;
    while (message[i] != NULL)
    {
        printf("\033[%d;%dH\033[33m%s\033[0m", message_start + i, (WIDTH - message_width) / 2, message[i]);
        i++;
    }
}

void matrix_effect()
{
    int cols[WIDTH] = {0};
    srand(time(NULL));

    while (1)
    {
        clear_screen();
        draw_matrix(cols);
        display_message();
        fflush(stdout);
        usleep(DELAY);

        if (rand() % 50 == 0) // Arrête après quelques cycles
            break;
    }
    clear_screen();
}
