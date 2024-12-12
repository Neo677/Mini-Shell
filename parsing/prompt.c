//      header

#include "minishell.h"

void ft_print_tokens(t_token *head)
{
    t_token *current = head;
    while (current)
    {
        printf("[TOKEN] Type: %d, Value: '%s'\n", current->type, current->value);
        current = current->next;
    }
}
