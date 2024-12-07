// header

#include "minishell.h"

//int main(int ac, char **av, char **env)

void    ft_intro(void)
{
    ft_printf("     #########################################\n");
    ft_printf("     #        WELCOME TO MINISHELL LAND      #\n");
    ft_printf("     #        LEXER PART BY thobenel         #\n");
    ft_printf("     #########################################\n");
    ft_printf("     #########################################\n\n");
    ft_printf("  Enter command below for tokenize that shit 🧑‍🍳 \n");
    ft_printf("  type 'exit' to quit this shell dude  \n");
}

void    ft_print_token(t_token *token)
{
    t_token *current;

    printf("\n Token genere: \n");
    printf("-----------------------------------\n");
    current = token;
    while(current)
    {
        ft_printf(" 👀 type = %d, value = %s\n", token->type, token->value);
        token = token->next;
    }
    printf("-----------------------------------\n\n");

}


int main(int ac, char **av, char **env)
{
    char *input;
    t_token *token;

    (void)ac;
    (void)av;
    (void)env;
    ft_intro();
    while (1)
    {
        input = readline("minishell > ");
        if (!input)
        {
            printf("[INFO]  exiting mini-shell  😔 \n");
            break;
        }
        if (*input)
            add_history(input);
        if (ft_strcmp(input, "exit") == 0)
        {
            free(input);
            printf("[INFO]  Bye Bye ! \n");
            break;
        }
        ft_printf("[INFO]  Tokenizing input: '%s'\n", input);
        token = ft_split_token(input);
        if (!token)
        {
            printf("🚨  Error token  🚨\n");
            continue;
        }
        printf("🤑  Token generated successfully\n");
        ft_print_token(token);
        if (!ft_valid_token(token))
        {
            printf("🚨  Error syntax  🚨\n");
            ft_free_token(token);
            continue;
        }
        printf("🤑  [sucess] token validated successfully\n");
        // ft_print_token(token);

        // todo : Appeler la fonction de parsing pour transformer en structure de commandes

        // todo : Executer les commandes une fois le parsing terminer

        // Libérer les ressources
        ft_free_token(token);
    }
    return (0);
}