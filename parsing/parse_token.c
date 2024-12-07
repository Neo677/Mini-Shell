// header

#include "minishell.h"

/*
                    🚨    🚨    🚨
    07/12/24
        Now that i finish to take an input / split it / check for every carac / set in an enum struct 
        for reference it for the parser can regnoize the commande.
        Now i can add the arg, redirections, pipe in a struct cmd.
                ⛓️⛓️⛓️
    1) Crée une commande vide 
    2) Gestions de lerreur d'alloc (leak safe)
    3) marque la commande qui contient un pipe
    4) arrete le parsing pour laisser un pipe gerer les commande suivante
    5) add une redicretions a la commande
    6) free
    7) add un arguments a la commande
    8) free
*/

t_command *ft_parse_token(t_token *token)
{
    t_command *command;
    t_token *current;

    command = ft_create_command(); // 1.
    if (!command)
        return (NULL); // 2. 
    current = token;
    while (current)
    {
        if (current->type == TOKEN_PIPE)
        {
                // 3.
            command->p_pipe = 1;
            current = current->next;
            break; // 4. 
        }
        else if (current->type == TOKEN_IN ||
                current->type == TOKEN_OUT ||
                current->type == TOKEN_HEREDOC ||
                current->type == TOKEN_APPEND)
        {
            // 5.
            if (!ft_add_redirections(command, current->type, current->value))
            {
                printf("Erreur : echec de l'ajout d'une de redirections\n");
                ft_free_command(command); // todo // 6.
                return (NULL);
            }
        }
        else if (current->type == TOKEN_WORD)
        {
            // 7.
            if (!ft_add_arguments(command, current->value))
            {
                printf("Erreur : echec de l'ajout d'un argument\n");
                ft_free_command(command); // todo // 6.
                return (NULL);
            }
        }
        else
        {
            printf("Erreur : token inconnue\n");
            ft_free_command(command); // todo // 6.
            return (NULL);
        }
        current = current->next;
    }
    return (command);
}
