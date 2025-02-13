/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 04:59:15 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/13 04:59:17 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command *ft_init_command(t_command **lst)
{
    t_command *new_cmd;
    t_command *last;

    new_cmd = malloc(sizeof(t_command));
    if (!new_cmd)
        return (ft_printf_fd(STDERR_FILENO, "minishell: memory failed for t_command\n"), NULL);
    new_cmd->arg = NULL;
    new_cmd->redirections = NULL;
    new_cmd->p_pipe = 0;
    new_cmd->next = NULL;
    if (*lst)
    {
        last = *lst;
        while (last->next)
            last = last->next;
        last->next = new_cmd;
    }
    else
        *lst = new_cmd;
    return (new_cmd);
}
