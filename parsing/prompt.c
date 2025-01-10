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

void	ft_print_tokens(t_token *head)
{
	t_token	*current;
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
	//ft_printf(" 👨‍🍳     LEXER PART     👨‍🍳 \n");
	while (current)
	{
		printf("Type: %s, Value: '%s'\n", token_type_name[current->type],
			current->value);
		current = current->next;
	}
}

void	ft_print_tab(char **tab)
{
	int	i;

	if (!tab)
	{
		ft_printf("[ERROR] tab est NULL\n");
		return;
	}
	i = 0;
	while (tab[i])
	{
		ft_printf("arg[%s]\n", tab[i]);
		i++;
	}
}

void	ft_print_redirections(t_redirections *head)
{
	t_redirections	*current;

	current = head;
	if (current == NULL)
	{
		printf("redirections is not here\n");
		return;
	}
	while (current)
	{
		if (current->type == TOKEN_IN)
		{
			ft_printf("redirec file = TOKEN_IN '<'\n");
		}
		else if (current->type == TOKEN_OUT)
		{
			ft_printf("redirec file = TOKEN_OUT '>'\n");
		}
		else if (current->type == TOKEN_APPEND)
		{
			ft_printf("redirec file = TOKEN APPEND '>>'\n");
		}
		else if (current->type == TOKEN_HEREDOC)
		{
			ft_printf("redirec file = TOKEN_HEREDOC '<<'\n");
		}
		if (current->file)
		{
			ft_printf("filename = %s\n", current->file);
		}
		//ft_printf("Type = %s\n", redirections_str[current->type]);
		//ft_printf("Redirec file = %s\n", current->type);
		current = current->next;
	}
}

void	ft_print_command_lst(t_command *head)
{
	int	i;
	t_command *current;

	current = head;
	if (current == NULL)
	{
		ft_printf("no command\n");
		return ;
	}
	i = 0;
	while (current)
	{
		if (head->arg)
		{
			i = 0;
			while (head->arg[i])
			{
				ft_printf("arg[%d]\n", head->arg[i]);
				i++;
			}
		}
		//ft_printf("head = %s\n", head->arg);
		ft_printf("t_command = pipe: %d\n", current->p_pipe); // Si on l’utilises
		ft_printf("args: \n");
		ft_print_tab(current->arg);          // Affiche arg[]
		ft_printf("redirections: \n");
		ft_print_redirections(current->redirections);
		ft_printf("----------------------------------\n");
		current = current->next;
		i++;
	}
}
