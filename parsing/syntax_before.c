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

// static bool	ft_set_syntax_quote(const char *input, int *quote)
// {
// 	if (*quote == 0)
// 		*quote = *input;
// 	else if (*quote == *input)
// 		*quote = 0;
//     return (*quote != 0);
// }

void    ft_pass_this_bro(t_parse_context *ctx)
{
    ctx->exit_status = 2;
}

void    ft_print_err_global(int i)
{
    if (i == 0)
        ft_printf_fd(2, "minishell: syntax error: unclosed quote\n");
    if (i == 1)
        ft_printf_fd(2, "minishell: syntax error near unexpected token `|'\n");
    if (i == 2)
        ft_printf_fd(2, "minishell: syntax error near unexpected token `newline'\n");
}

static int	ft_set_syntax_quote(const char *input, t_parse_context *ctx)
{
    int quote;
    int i;

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

static int ft_set_syntax_pipe(const char *input, int i, t_parse_context *ctx)
{
    int j;

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
        ft_printf_fd(2, "bash: syntax error near unexpected token `%c'\n", input[j]); // line too long 
        return (ft_pass_this_bro(ctx), -1);
    }
    return (j);
}



void ft_set_syntax_redir_1(int len, char op)
{
    ft_printf_fd(2, "minishell: syntax error near unexpected token `");

    if (op == '>')
    {
        if (len <= 2)
        {
            /* Pour '>' et '>>', l'argument manque → on affiche "newline" */
            ft_printf_fd(2, "newline");
        }
        else if (len == 3)
        {
            /* Pour '>>>', on affiche le token ">" */
            ft_printf_fd(2, "%c", op);
        }
        else /* len >= 4 */
        {
            /* Pour 4 '>' ou plus, on affiche toujours le token ">>" */
            ft_printf_fd(2, ">>");
        }
    }
    else if (op == '<')
    {
        if (len <= 3)
        {
            /* Pour '<', '<<' ou '<<<', l'argument manque → on affiche "newline" */
            ft_printf_fd(2, "newline");
        }
        else if (len == 4)
            ft_printf_fd(2, "<");
        else if (len == 5)
            ft_printf_fd(2, "<<");
        else
            ft_printf_fd(2, "<<<");
    }
    ft_printf_fd(2, "'\n");
}

void ft_set_syntax_redir_2(const char *input, int j)
{
    ft_printf_fd(2, "minishell: syntax error near unexpected token ");
    if (!input[j])
        ft_printf_fd(2, "`newline'\n");
    else
        ft_printf_fd(2, "`%c'\n", input[j]);
}

static int ft_set_syntax_ope(const char *input, int i, t_parse_context *ctx)
{
    char op = input[i];
    int len = 0;
    int j = i;

    /* Comptage des opérateurs consécutifs */
    while (input[j] == op)
    {
        len++;
        j++;
    }

    /* Vérification de la validité du groupe d'opérateurs :
     * - Pour '>' : seuls les groupes de 1 et 2 sont considérés comme syntaxiquement corrects.
     * - Pour '<' : seul le groupe de 1 est correct.
     */
    if ((op == '>' && len > 2) || (op == '<' && len != 1))
    {
        ft_set_syntax_redir_1(len, op);
        ft_pass_this_bro(ctx);  /* Met à jour le code d'erreur à 2 */
        return -1;
    }

    /* On ignore les espaces ou tabulations après la redirection */
    while (input[j] && (input[j] == ' ' || input[j] == '\t'))
        j++;

    /* Vérification de l'argument attendu après la redirection */
    if (!input[j] || input[j] == '|' || input[j] == '>' || input[j] == '<')
    {
        ft_set_syntax_redir_2(input, j);
        ft_pass_this_bro(ctx);
        return -1;
    }
    return j;
}


int  ft_check_syntax(const char *input, t_parse_context *ctx)
{
    int i;
    int res;

    // ctx->exit_status = 0;
    if (ft_set_syntax_quote(input, ctx) == 0)
        return (0);
    i = 0;
    while (input[i])
    {
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

// int	ft_check_syntax(const char *input)
// {
// 	char	current;
// 	int		quote;

// 	quote = 0;
// 	while (*input)
// 	{
// 		if (*input == ' ')
// 			input++;
// 		else if (*input == '\'' || *input == '\"')
// 			ft_set_syntax_quote(input, &quote);
// 		else if (*input == '|')
// 		{
// 			if (ft_set_syntax_pipe(input) == 0)
// 				return (0);
// 			input++;
// 		}
// 		else if (*input == '<' || *input == '>')
// 		{
// 			current = *input;
// 			if (ft_set_syntax_redir(current, input) == 0)
// 				return (0);
// 			input++;
// 				return (0);
// 		}
// 		input++;
// 	}
// 	if (quote != 0)
// 		return (ft_printf("[🚨 ERROR 🚨] Syntax error: unclosed quote\n"), 0);
// 	return (1);
// }

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
