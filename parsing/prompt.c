// header

#include "minishell.h"

// void    ft_load_name_user() todo

/*
void    ft_print_prompt() // todo
{

}
*/

void    ft_print_token(t_token *token)
{
    while(token)
    {
        ft_printf(" 👀 type = %d, value = %s\n", token->type, token->value);
        token = token->next;
    }
}
