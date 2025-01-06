// header

#include "minishell.h"

void ft_start_minishell(void)
{
    char *input;
    t_token *token;

    while (1)
    {
        input = readline("$> ");
        if (!input) // Gestion de Ctrl-D ou erreur de readline
        {
            ft_printf("\n Bye bye ! 👋 \n");
            break;
        }
        if (ft_strcmp(input, "exit") == 0)
        {
            ft_printf("Bye bye ! 👋 \n");
            free(input);
            break;
        }
        if (input[0] == '\0')
        {
            free(input);
            continue;
        }
        add_history(input);
        token = ft_parse_token(input);
        if (!token)
        {
            free(input); // printf("[ERROR] Invalid syntax\n"); // Message d'erreur informatif
            continue;
        }
        
        ft_clean_up(&token, &input); // Autres étapes (par exemple, exécution de la commande)
    }
}
