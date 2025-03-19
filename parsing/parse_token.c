/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:08 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/18 19:21:25 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_parse_token(const char *input, t_env **env_cpy, t_command **cmd_lst,
		int *last_exit_status)
{
	t_token			*token;
	t_parse_context	ctx;

	*cmd_lst = NULL;
	token = NULL;
	if (!input || !*input)
		return (NULL);
	if (!ft_split_token(&token, input, env_cpy, last_exit_status))
		return (NULL);
	if (ft_create_command_lst(token, cmd_lst, &ctx) == 0)
	{
		ft_printf_fd(2, "minishell: parser error: failed to \
				create command list\n");
		ft_free_token(token);
		ft_free_commande_lst(*cmd_lst);
		return (NULL);
	}
	return (token);
}
