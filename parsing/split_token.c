// header

#include "minishell.h"

/*
                    🚨    🚨    🚨
    separe input brut en morceaux de texte interpreter comme des tokens
    1) ignorer les white space
    2) handle quote (simple ou double)
    3) hande operator (pipe, redirections)
    4) handle word (arg, command)
*/

void    ft_split_token(t_token **head, const char *input)
{
    char *quote;

    while (*input)
    {
        if (*input == ' ' || *input == '\t')
            input++;
        else if (*input == '\'' || *input == '\"')
        {
            quote = ft_handle_quote(&input, *input);
            if (!quote)
            {
                printf("Erreurs : quote non ferme.\n");
                return;
            }
            ft_add_token(head, ft_create_token(TOKEN_WORD, quote));
        }
        else if (*input == '>' || *input == '<' || *input == '|')
            ft_handle_operator(head, &input);
        else
            ft_handle_word(head, &input);
    }
}
