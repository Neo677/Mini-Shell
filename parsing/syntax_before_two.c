/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_before_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:27:49 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 08:27:51 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pass_this_bro(t_parse_context *ctx)
{
	ctx->exit_status = 2;
}

void	ft_print_err_global(int i)
{
	if (i == 0)
		ft_printf_fd(2, "bash: syntax error: unclosed quote\n");
	if (i == 1)
		ft_printf_fd(2, "bash: syntax error near unexpected token `|'\n");
	if (i == 2)
		ft_printf_fd(2, "bash: syntax error near unexpected token `newline'\n");
}

int	ft_set_syntax_quote(const char *input, t_parse_context *ctx)
{
	int	quote;
	int	i;

	quote = 0;
	i = 0;
	while (input[i] == '\'' || input[i] == '"')
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (quote == 0)
				quote = input[i];
			else if (quote == input[i])
				quote = 0;
		}
		i++;
	}
	if (quote != 0)
		return (ft_print_err_global(0), ft_pass_this_bro(ctx), 0);
	return (1);
}

int	ft_set_syntax_pipe(const char *input, int i, t_parse_context *ctx)
{
	int	j;

	j = 0;
	if (i == 0)
		return (ft_print_err_global(1), ft_pass_this_bro(ctx), -1);
	j = i + 1;
	while (input[j] && (input[j] == ' ' || input[j] == '\t'))
		j++;
	if (!input[j])
		return (ft_print_err_global(2), ft_pass_this_bro(ctx), -1);
	if (input[j] == '|' || input[j] == '<' || input[j] == '>')
	{
		ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n",
			input[j]);
		return (ft_pass_this_bro(ctx), -1);
	}
	return (j);
}
