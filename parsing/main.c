// header

#include "minishell.h"

int main(int ac, char **av, char **env)
{
    char *input;
    t_token *token;

    (void)ac;
    (void)av;
    (void)env;
   //ft_intro();
    printf("\033[?25l"); // Cache le curseur
    //matrix_effect();
    printf("\033[?25h"); // Affiche le curseur
    while (1)
    {
        input = readline("$> "); // posibilite de leak (readline)
        if (!input)
        {
            error_exit("Bye bye ! 👋 \n");
            break;
        }
        ft_printf("[INFO]  Tokenizing input: '%s'\n", input);
        ft_handle_exit(input);
        token = ft_parse_token(input);
        ft_print_tokens(token);
        ft_clean_up(&token, &input);
    }
    return (0);
}

