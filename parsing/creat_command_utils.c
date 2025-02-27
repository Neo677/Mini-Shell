#include "minishell.h"

void	ft_create_cmd_pipe(t_command **current)
{
	if (*current)
		(*current)->p_pipe = 1;
	*current = NULL;
}

int ft_create_cmd_word(t_command **current, t_token *token, t_command **lst)
{
    if (!(*current))
    {
        *current = ft_init_command(lst);
        if (!*current)
            return (ft_free_command_list(lst), 0);
    }
    if (!ft_add_arguments(*current, token->value))
    {
        ft_printf_fd(STDERR_FILENO, "minishell: failed to add argument\n");
        ft_free_command_list(lst);
        return (0);
    }
    return (1);
}

int	ft_create_cmd_redirect(t_command **current, t_token *token, t_command **lst)
{
	const char	*file;

	if (!(*current))
	{
		*current = ft_init_command(lst);
		if (!*current)
			return (ft_free_command_list(lst), 0);
	}
	if (!token->next || token->next->type != TOKEN_WORD)
		return (ft_free_command_list(lst), 0);
	file = token->next->value;
	if (!ft_add_redirections_struct(*current, token->type, file))
		return (ft_free_command_list(lst), 0);
	return (1);
}

int	ft_create_cmd_env(t_command **current, t_token *token, t_command **lst)
{
	if (!(*current))
	{
		*current = ft_init_command(lst);
		if (!*current)
			return (ft_free_command_list(lst), 0);
	}
	if (!ft_add_arguments(*current, token->value))
		return (ft_free_command_list(lst), 0);
	return (1);
}
