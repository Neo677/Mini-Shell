// header

#include "minishell.h"

int     ft_is_redirections(t_token *token)
{
    return (token->type == TOKEN_IN || token->type == TOKEN_OUT || 
            token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC);
}

int ft_valid_pipes(t_token *token, t_token *prev)
{
    if (token->type == TOKEN_PIPE)
    {
        if (!prev || !token->next)
            return (0);
        if (prev->type == TOKEN_PIPE)
            return (0);
    }
    return (1);
}


char *ft_handle_quotes(char **current, char quote_type)
{
    char *start;
    char *value;

    (*current)++; // suate louverture de la quote
    start = *current;
    while (**current && **current != quote_type)
        (*current)++;
    if (**current == '\0') // erreur si quote non fermer 
    {
        ft_printf(" Error : Unclosed quote\n");
        return (NULL);
    }
    value = ft_strndup(start, *current - start);
    (*current)++; // sauter la fermeture de la quote
    return (value);

}

/*
                    🚨    🚨    🚨
    need to check error on the the type of token :
    1) pipe is invalid if is it on the begining or at the end
    2) double pipe ar an error (|  |)
    3) check error on redirection 
        A) every redirection muste be follow by a file or an arg valide
            (<, >, >>, <<)
        B) one redirection is valide
    4) the quote must be set on a valide content
    5) the part can be adapt for the handling on quote
        (ex : if she exented on many token)
*/

int ft_valid_token(t_token *token)
{
    t_token *prev = NULL;

    while (token)
    {
        // Vérifier si le pipe est valide
        if (token->type == TOKEN_PIPE)
        {
            if (!prev || !token->next || prev->type == TOKEN_PIPE)
            {
                ft_printf("🚨 Error: Invalide pipe usage\n");
                return (0); // Pipe au début, à la fin, ou double pipe
            }
                
        }

        // Vérifier si la redirection est suivie d'un fichier/argument valide
        if (ft_is_redirections(token))
        {
            if (!token->next || token->next->type != TOKEN_WORD)
            {
                ft_printf("  🚨 Error: Redirections wihout a valid file/arguments\n");
                return (0); // Redirection sans argument valide
            }
                
        }

        // Vérifier les quotes
        if (token->type == TOKEN_QUOTE || token->type == TOKEN_DBL_QUOTE)
        {
            if (!ft_handle_quotes(&token->value, token->type))
                return (0); // Gestion des quotes échouée
        }
        prev = token; // Mettre à jour le token précédent
        token = token->next; // Passer au token suivant
    }
    return (1); // Valide si toutes les vérifications passent
}
