#include "minishell.h"

void    ft_create_cmd_pipe(t_command *current, t_token *token)
{
    if (current)
        current->p_pipe = 1;
    current = NULL;
    token = token->next;
}

int    ft_create_cmd_word(t_command *current, t_token *token, t_command **lst)
{
    if (!current && !(current = ft_init_command(lst)))
    {
        return (ft_free_command_list(lst), 0);
    }
    if (!ft_add_arguments(current, token->value))
    {
        ft_printf_fd(2, "minishell: failed to add argument\n");
        return (ft_free_command_list(lst), 0);
    }
    token = token->next;
    return (1);
}

int    ft_create_cmd_redirect(t_command *current, t_token *token, t_command **lst, const char *file)
{
    if (!current && !(current = ft_init_command(lst)))
    {
        return (ft_free_command_list(lst), 0);
    }
    if (!token->next || token->next->type != TOKEN_WORD)
    {
        ft_printf_fd(2, "minishell: syntax error near redirection\n");
        return (ft_free_command_list(lst), 0);
    }
    file = token->next->value;
    if (!ft_add_redirections_struct(current, token->type, file))
    {
        ft_printf_fd(2, "minishell: syntax error near unexpected token\n");
        return (ft_free_command_list(lst), 0);
    }
    token = token->next;
    return (1);
}

int    ft_create_cmd_env(t_command *current, t_token *token, t_command **lst)
{
    if (!current && !(current = ft_init_command(lst)))
        return (ft_free_command_list(lst), 0);
    if (!ft_add_arguments(current, token->value))
    {
        ft_printf_fd(2, "minishell: failed to add envrionnement varibles as arugments\n");
        return (ft_free_command_list(lst), 0);
    }
    token = token->next;
    return (1);
}