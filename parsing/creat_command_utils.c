/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_command_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:19:07 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:20:24 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_cmd_pipe(t_command **current)
{
	if (*current)
		(*current)->p_pipe = 1;
	*current = NULL;
}

int	ft_create_cmd_word(t_command **current, t_token *token, t_command **lst)
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

int	ft_create_cmd_redirect(t_command **current, t_token *token, t_command **lst,
		t_parse_context *ctx)
{
	const char	*file;

	file = token->next->value;
	if (!current || !token || !lst)
		return (0);
	if (!(*current))
	{
		*current = ft_init_command(lst);
		if (!(*current))
		{
			ft_free_command_list(lst);
			return (0);
		}
	}
	if (!token->next || token->next->type != TOKEN_WORD)
	{
		ft_free_command_list(lst);
		return (0);
	}
	if (!ft_add_redirections_struct(*current, token->type, file, ctx))
	{
		ft_free_command_list(lst);
		return (0);
	}
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
	token = token->next;
	return (1);
}
