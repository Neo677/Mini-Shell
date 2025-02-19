

#include "../include/exec.h"

// int check_file(t_token *token)
// {
//     int infile;
//     int outfile;
//     t_parse_context ctx;

//     while (token)
//     {
//         if (token->type == 2)
//         {
//             if (token->next->type == 0)
//             {
//                 infile = open(token->next->value, O_RDONLY, 0644);
//                 if (infile < 0)
//                 {
//                     ft_printf_fd(2, "bash: ");
//                     perror(token->next->value);
//                     return (ctx.exit_status = 1);
//                 }
//             }
//         }
//         if (token->type == 3)
//         {
//             if (token->next->type == 0)
//             {
//                 outfile = open(token->next->value, O_TRUNC | O_CREAT | O_WRONLY, 0644);
//                 if (outfile < 0)
//                 {
//                     ft_printf_fd(2, "bash: ");
//                     perror(token->next->value);
//                     return (ctx.exit_status = 1);
//                 }
//             }
//         }
//         token = token->next;
//     }
//     return (0);
// }

int check_file_in(t_token *token, t_parse_context ctx)
{
    int infile;

    if (token->type == 2)
    {
        if (token->next->type == 0)
        {
            infile = open(token->next->value, O_RDONLY, 0644);
            if (infile < 0)
            {
                ft_printf_fd(2, "bash: ");
                perror(token->next->value);
                return (ctx.exit_status = 1);
            }
        }
    }
    return (0);
}

int check_file_out(t_token *token, t_parse_context ctx)
{
    int outfile;

    if (token->type == 3)
    {
        if (token->next->type == 0)
        {
            outfile = open(token->next->value, O_TRUNC | O_CREAT | O_WRONLY, 0644);
            if (outfile < 0)
            {
                ft_printf_fd(2, "bash: ");
                perror(token->next->value);
                return (ctx.exit_status = 1);
            }
        }
    }
    return (0);
}

int check_file(t_token *token)
{
    t_parse_context ctx;

    while (token)
    {
        if (check_file_in(token, ctx) != 0)
            return (ctx.exit_status = 1);
        if (check_file_out(token, ctx) != 0)
            return (ctx.exit_status = 1);
        token = token->next;
    }
    return (0);
}
