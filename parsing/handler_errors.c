//          header

#include "minishell.h"

void ft_error_pipe(const char *context)
{
    printf(" [🚨ERROR 🚨] pipe error minishell = '%s'\n", context);
}

int ft_error_redirections(const char *context)
{
    printf(" [🚨ERROR🚨] redirec minishell : syntax error = near unexpected token '%s'\n", context);
    return (0);
}

int ft_error_quote(void)
{
    printf(" [🚨ERROR🚨] quote minishell : syntax error = unclosed quote\n");
    return (0);
}

int ft_error_general(const char *context)
{
    printf(" [🚨ERROR🚨] gen minishell : error = %s\n", context);
    return (0);
}

int ft_error_env(const char *context)
{
    printf(" [🚨ERROR🚨] gen minishell : error = %s\n", context);
    return (0);
}
