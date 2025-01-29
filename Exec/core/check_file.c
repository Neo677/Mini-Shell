

#include "../include/pipex.h"

int check_file(t_token *token)
{
    int infile;
    int outfile;

    while (token)
    {
        if (token->type == 2)
        {
            if (token->next->type == 0)
            {
                infile = open(token->next->value, O_RDONLY, 0644);
                if (infile < 0)
                {
                    ft_printf_fd(2, "bash: ");
                    perror(token->next->value);
                    return (-1);
                }
            }
        }
        if (token->type == 3)
        {
            if (token->next->type == 0)
            {
                outfile = open(token->next->value, O_TRUNC | O_CREAT | O_WRONLY, 0644);
                if (outfile < 0)
                {
                    ft_printf_fd(2, "bash: ");
                    perror(token->next->value);
                    return (-1);
                }
            }
        }
        token = token->next;
    }
    return (0);
}