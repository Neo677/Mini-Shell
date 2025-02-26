/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_before.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:20:12 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/12 01:14:22 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	the purpose of the syntax fonction :
	1) is to check the syntax global of the input before every single operations,
	2) She check if a big syntax error like quote not closed or anything else ...
	3) if an error is detected is unusless to keep going the lexing

   -Ignorer les espaces
   -Gestion des quotes
   -Quote ouverte
   -Quote fermée
   -Validation des pipes
   -Ignorer les espaces après le pipe
   -Validation des redirections
   -Ignorer les espaces après la redirection
   -Erreur si une quote reste ouverte
*/

void	ft_pass_this_bro(t_parse_context *ctx)
{
	ctx->exit_status = 258;
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

static int	ft_set_syntax_quote(const char *input, t_parse_context *ctx)
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

static int	ft_set_syntax_pipe(const char *input, int i, t_parse_context *ctx)
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

void	ft_set_syntax_redir_1(int len, char op)
{
	ft_printf_fd(2, "bash: syntax error near unexpected token `");
	if (op == '>')
	{
		if (len <= 2)
			ft_printf_fd(2, "newline");
		else if (len == 3)
			ft_printf_fd(2, "%c", op);
		else
			ft_printf_fd(2, ">>");
	}
	else if (op == '<')
	{
		if (len <= 3)
			ft_printf_fd(2, "newline");
		else if (len == 4)
			ft_printf_fd(2, "<");
		else if (len == 5)
			ft_printf_fd(2, "<<");
		else
			ft_printf_fd(2, "<<<");
	}
	ft_printf_fd(2, "'\n");
}

void	ft_set_syntax_redir_2(const char *input, int j)
{
	ft_printf_fd(2, "bash: syntax error near unexpected token ");
	if (!input[j])
		ft_printf_fd(2, "`newline'\n");
	else
		ft_printf_fd(2, "`%c'\n", input[j]);
}

static int	ft_set_syntax_ope(const char *input, int i, t_parse_context *ctx)
{
	char	op;
	int		len;
	int		j;

	op = input[i];
	len = 0;
	j = i;
	while (input[j] == op)
	{
		len++;
		j++;
	}
	if ((op == '>' && len > 2) || (op == '<' && len != 1))
		return (ft_set_syntax_redir_1(len, op), ft_pass_this_bro(ctx), -1);
	while (input[j] && (input[j] == ' ' || input[j] == '\t'))
		j++;
	if (!input[j] || input[j] == '|' || input[j] == '>' || input[j] == '<')
		return (ft_set_syntax_redir_2(input, j), ft_pass_this_bro(ctx), -1);
	return (j);
}

int	ft_check_syntax(const char *input, t_parse_context *ctx)
{
	int	i;
	int	res;

	if (ft_set_syntax_quote(input, ctx) == 0)
		return (0);
	i = 0;
	while (input[i])
	{
		if (input[i] == '!')
			return (ft_printf_fd(2,
					"bash: syntax error near unexpected token `newline'\n"),
				ft_pass_this_bro(ctx), 0);
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			if (input[i] == '|')
				res = ft_set_syntax_pipe(input, i, ctx);
			if (input[i] == '>' || input[i] == '<')
				res = ft_set_syntax_ope(input, i, ctx);
			if (res < 0)
				return (0);
			i = res;
		}
		i++;
	}
	return (1);
}
