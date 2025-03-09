/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:27:58 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/06 13:35:52 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_redirec_pipe(t_parse_context *ctx)
{
	if (**ctx->input == '|')
		return (0);
	if (**ctx->input == '>' || **ctx->input == '<')
		return (0);
	return (1);
}

void	ft_let_go_split_env(t_parse_context ctx, int *last_exit_status)
{
	printf("\n");
	ft_free_commande_lst(*ctx.cmd_lst);
	ft_free_token(*ctx.head);
	*last_exit_status = ctx.exit_status;
}

void	ft_handle_exclam(t_parse_context *ctx, int *last_exit_status)
{
	ctx->exit_status = 1;
	*last_exit_status = ctx->exit_status;
}

int	process_tokens(t_parse_context *ctx, int *last_exit_status)
{
	while (**ctx->input)
	{
		if (**ctx->input == ' ' || **ctx->input == '\t' || **ctx->input == ':')
			(*ctx->input)++;
		else if (**ctx->input == '\'' || **ctx->input == '"')
		{
			if (!ft_handle_quotes(ctx))
				return (ft_let_go_split(*ctx, last_exit_status), 0);
		}
		else if (**ctx->input == '!')
			return (ft_handle_exclam(ctx, last_exit_status), 0);
		else if (ft_is_redirec_pipe(ctx) == 0)
		{
			if (!ft_handle_operators(ctx))
				return (ft_let_go_split(*ctx, last_exit_status), 0);
		}
		else if (**ctx->input == '$')
		{
			if (!ft_handle_env_vars(ctx))
					// return (ft_let_go_split_env(*ctx, last_exit_status);
			(*ctx->input)++;
		}
		else
		{
			if (!ft_handle_words(ctx))
				return (ft_let_go_split(*ctx, last_exit_status), 0);
		}
	}
	return (1);
}
