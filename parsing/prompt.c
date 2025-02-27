/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:13 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:14 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tab(char **tab)
{
	int	i;

	if (!tab)
	{
		ft_printf("[DEBUG] tab est NULL\n");
		return ;
	}
	i = 0;
	while (tab[i])
	{
		ft_printf("[DEBUG] arg = [%s]\n", tab[i]);
		i++;
	}
}

void	ft_print_redirections(t_redirections *head)
{
	t_redirections	*current;

	current = head;
	while (current != NULL)
	{
		if (current->type == TOKEN_IN)
			ft_printf("[DEBUG] redirec file = TOKEN_IN = %s '<'\n",
				current->file);
		else if (current->type == TOKEN_OUT)
			ft_printf("[DEBUG] redirec file = TOKEN_OUT = %s '>'\n",
				current->file);
		else if (current->type == TOKEN_APPEND)
			ft_printf("[DEBUG] redirec file = TOKEN APPEND  = %s '>>'\n",
				current->file);
		else if (current->type == TOKEN_HEREDOC)
			ft_printf("[DEBUG] redirec file = TOKEN_HEREDOC  = %s '<<'\n",
				current->file);
		if (current->file)
			ft_printf("[DEBUG] filename = %s\n", current->file);
		else
			ft_printf("[DEBUG] redirections is not here\n");
		current = current->next;
	}
}

void	ft_print_command_lst(t_command *head)
{
	t_command	*current;

	current = head;
	if (current == NULL)
	{
		ft_printf("[DEBUG] no command\n");
		return ;
	}
	ft_printf("\n-------------[DEBUG]---------------\n");
	while (current)
	{
		ft_printf("\n[DEBUG] t_command = pipe: %d\n", current->p_pipe);
		ft_print_tab(current->arg);
		ft_print_redirections(current->redirections);
		current = current->next;
	}
	ft_printf("----------------------------------\n");
	ft_free_commande_lst(current);
}

void	ft_print_tokens(t_token *head)
{
	t_token		*current;
	const char	*token_type_name[] = {
	[TOKEN_WORD] = "TOKEN_WORD",
	[TOKEN_PIPE] = "TOKEN_PIPE",
	[TOKEN_IN] = "TOKEN_IN",
	[TOKEN_OUT] = "TOKEN_OUT",
	[TOKEN_APPEND] = "TOKEN_APPEND",
	[TOKEN_HEREDOC] = "TOKEN_HEREDOC",
	[TOKEN_ENV_VAR] = "TOKEN_ENV_VAR",
	[TOKEN_QUOTE] = "TOKEN_QUOTE",
	[TOKEN_DBL_QUOTE] = "TOKEN_DBL_QUOTE",
	[TOKEN_ERROR] = "TOKEN_ERROR",
	};

	current = head;
	while (current)
	{
		printf("Type: %s, Value: '%s'\n", token_type_name[current->type],
			current->value);
		current = current->next;
	}
}
