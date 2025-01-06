// header

#include "minishell.h"

/*
    the purpose of the syntax fonction
    is to check the syntax global of the input, 
    before every single operations,
    She check if a big syntax error like quote or anything else ...
    if an error is detected is unusless to keep going the parsing
    because the entry is globaly Wrong
*/

int ft_check_syntax(const char *input)
{
    int quote;

    quote = 0;
    while (*input)
    {
        if (*input == '\'' || *input == '\"')
        {
            if (quote == 0)
                quote = *input;
            else if (quote == *input)
                quote = 0;
        }
        if (*input == '|')
            if (*(input + 1) == '|' || *(input + 1) == '\0')
                return(printf("[🚨 ERROR 🚨] Syntax error: empty pipe\n"), 0);
        if (*input == '<' || *input == '>')
            if (*(input + 1) == '\0' || (*(input + 1) != ' ' && *(input + 1) != '<' && *(input + 1) != '>'))
                return(printf("[🚨 ERROR 🚨] Syntax error: incomplete redirections\n"), 0);
        input++;
    }
    if (quote != 0)
        return (printf("[🚨 ERROR 🚨] Syntax error: unclosed quote\n"), 0);
    return (1);
}
