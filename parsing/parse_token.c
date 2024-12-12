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

t_token *ft_parse_token(const char *input)
{
    t_token *token;
    t_command *cmd_lst;

    cmd_lst = NULL;
    token = NULL;
    if (!(input) || !(*input))
    {
        printf("[ERROR]  entrer vide\n");
        return (NULL);
    }
    ft_split_token(&token, input);
    if (!token)
        printf("[ERROR]  aucun token valide trouvee\n");
    if (ft_valid_token(token) == 0)
    {
        ft_free_token(token);
        printf("[ERROR] Token invalid detected\n");
        return (NULL);
    }
    ft_create_command_lst(token, &cmd_lst);
    //ft_free_token(token);
    return (token);
}
