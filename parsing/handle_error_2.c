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

void	ft_free_split(t_token *head, t_command *cmd_lst)
{
	ft_printf("[ERROR] Token invalid ! = %s\n", head->value);
	// ft_free_token(head);
	head = NULL;
	ft_free_commande_lst(cmd_lst);
}

void    ft_err_split(t_command *cmd_lst, t_token *head)
{
    ft_free_token(head);
    head = NULL;
    ft_free_commande_lst(cmd_lst);
	return;
}

void    ft_err_split_ope(t_command *cmd_lst, t_token *head)
{
	ft_printf("[ERROR] Échec de l'ajout de commande\n");
    ft_free_token(head);
    head = NULL;
    ft_free_commande_lst(cmd_lst);
	return;
}

void    ft_err_bad_redirec(t_command *cmd_lst, t_token *head)
{
	ft_printf("[ERROR] Redirection sans fichier valide\n");
    ft_free_token(head);
    head = NULL;
    ft_free_commande_lst(cmd_lst);
	return;
}
