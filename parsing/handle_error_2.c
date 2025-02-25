/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:18:49 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/13 13:18:56 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_split(t_token **head, t_command **cmd_lst,
		const char *error_msg, const char *token)
{
	if (error_msg && token)
		ft_printf_fd(STDERR_FILENO, "minishell: %s '%s' \n", error_msg, token);
	else if (error_msg)
		ft_printf_fd(STDERR_FILENO, "minishell: %s \n", error_msg);
	if (head)
	{
		ft_free_token(*head);
		*head = NULL;
	}
	if (cmd_lst && *cmd_lst)
	{
		ft_free_commande_lst(*cmd_lst);
		*cmd_lst = NULL;
	}
}

void	ft_err_split(t_command *cmd_lst, t_token *head)
{
	ft_free_token(head);
	head = NULL;
	ft_free_commande_lst(cmd_lst);
	free(cmd_lst);
	return ;
}

void	ft_err_split_ope(t_command *cmd_lst, t_token *head)
{
	ft_printf_fd(STDERR_FILENO, "minishell: failed to add the command\n");
	ft_free_token(head);
	head = NULL;
	ft_free_commande_lst(cmd_lst);
	cmd_lst = NULL;
	return ;
}

void	ft_err_bad_redirec(t_command *cmd_lst, t_token *head)
{
	ft_printf_fd(STDERR_FILENO,
		"syntax error near unexpected token `newline`\n");
	ft_free_token(head);
	head = NULL;
	ft_free_commande_lst(cmd_lst);
	return ;
}

int	error_cleanup(t_parse_context *ctx, int *last_exit_status)
{
	ft_free_commande_lst(*ctx->cmd_lst);
	ft_free_token(*ctx->head);
	*last_exit_status = ctx->exit_status;
	return (0);
}
