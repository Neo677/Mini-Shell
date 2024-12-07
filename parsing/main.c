// header

#include "minishell.h"

//int main(int ac, char **av, char **env)

int main(int ac, char **av)
{
    char *input;
    t_token *token;
    int valid;

    (void)ac;
    (void)av;
    printf("Welcome to minishell\n");
    while (1)
    {
        input = readline("minishell > ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
            add_history(input);
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            printf("exit\n");
            break;
        }
        // token = (input);
        if (!token)
        {
            printf("🚨  Error token  🚨\n");
            free(input);
            continue;
        }
        valid = ft_valid_token(token);
        if (!valid)
        {
            printf("🚨  Error syntax  🚨\n");
            ft_free_token(token);
            free(input);
            continue;
        }
        ft_print_token(token);

        // todo : Appeler la fonction de parsing pour transformer en structure de commandes

        // todo : Executer les commandes une fois le parsing terminer

        // Libérer les ressources
        ft_free_token(token);
        free(input);
    }
    return (0);
}