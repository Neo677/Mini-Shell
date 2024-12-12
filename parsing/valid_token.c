// header

#include "minishell.h"

int     ft_valid_redirections(t_token *token)
{
    while (token)
    {
        if (token->type == TOKEN_IN|| token->type == TOKEN_OUT || token->type == TOKEN_APPEND || token->type == TOKEN_HEREDOC)
        {
            if (!token->next || token->next->type != TOKEN_WORD)
            {
                printf("🚨 Error: Redirections wihout valid file/arguments\n");
                return (0);
            }
        }
        token = token->next;
    }
    return (1);
}

/*
    step for check if the quotes is valid :
    1) saute l'ouverture de la quote
    2) erreur si quote non fermer 
    3) sauter la fermeture de la quote

*/
char *ft_valid_quotes(char **current, char quote_type)
{
    char *start;
    char *value;

    (*current)++;
    start = *current;
    while (**current && **current != quote_type)
        (*current)++;
    if (**current == '\0')
    {
        ft_printf(" Error : Unclosed quote\n");
        return (NULL);
    }
    value = ft_strndup(start, *current - start);
    (*current)++;
    return (value);
}

/*
                    🚨    🚨    🚨
    Check the validity of :
    1) initialisation of the token before 
            (that why we got prev)
    2) check the pipe
        a. check if the pipe is valid
        b. the handle error mean if we got a pipe at the begining of the input
            or at the end, and if there is a double. 
            (ex : input = '| cat ...' or 'cat .. |' or 'cat ... || cat ...')
    3) check error on redirection 
        a. every redirection muste be follow by a file/arg valid (<, >, >>, <<)
        b. else return a faild (0)
    4) the quote must be set on a valide content
        a.check the quotes
        b. else return a faild (0)
    5) Updates the previous and the next token.
    6) return (1) if the token are good

    🧑‍💻  for a certain visiblity and of course norm i need to
    🧑‍💻  split this fonction but the purpose is the same
*/

/*
    utils for the parsing :
    chekc if the quote is correctly closed for 
    avoid a syntax error in the token
*/

int ft_validay_quotes(t_token *token)
{
    char *parsed_value;

    if (token->type == TOKEN_QUOTE || token->type == TOKEN_DBL_QUOTE)
    {
        parsed_value = ft_valid_quotes(&token->value, token->type);
        if (!parsed_value)
            return (0);
    }
    return (1);
}

//              probleme = when input is == '| ls | ls ||'
//                                infinite loop

int ft_validay_pipes(t_token *token)
{
    t_token *prev = NULL;

    while(token)
    {
        if (token->type == TOKEN_PIPE)
        {
            if (prev == NULL)
                return (0);
            if (prev->type == TOKEN_PIPE)
                return (0);
            if (!token->next)
                return(0);
        }
        prev = token;
        token = token->next;
    }
    return (1);
}

int ft_valid_env_var(t_token *token)
{
    while (token)
    {
        if (token->type == TOKEN_ENV_VAR)
        {
            if (!ft_strlen(token->value))
            {
                ft_error_env("invalid env var syntax :(");
                return (0);
            }
        }
        token = token->next;
    }
    return (1);
}


int ft_valid_token(t_token *token)
{
    while (token)
    {
        if (ft_validay_pipes(token) == 0)
        {
            ft_error_pipe("validay issue");
            return (0);
        }
            
        if (!ft_valid_redirections(token))
        {
            ft_error_redirections(token->value);
            return (0);
        }
        if (!ft_valid_env_var(token))
            return (0);
        if ((token->type == TOKEN_QUOTE || token->type == TOKEN_DBL_QUOTE)
            && (!ft_valid_quotes(&token->value, token->type)))
        {
            ft_error_quote();
            return (0);
        }
        token = token->next;
    }
    return (1); // Valide si toutes les vérifications passent
}
