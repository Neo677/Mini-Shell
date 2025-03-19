/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:18 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/13 02:25:36 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	cmd = Liste des commandes
	current = Commande courante

	1) Vérification de la syntaxe globale
	2) Parcours de la chaîne d'entrée
		A) ignorer les espaces et les tab
		B) gestions des quotes -> (ft_handle_quotes)
			a) ajout des token de type WORD
				↘️
					check fontions -> (ft_handle_quotes)
			b) creation de commande si necessaires, puis
				ajout en arguments
		C) Gestion des operateurs (pipe, redirections)
			a) appel de fonctions auxiliaire pour cree le token correcpondant
			b) gestion d'erreur dans la fonction
			c) si c'est un pipe, cree une nouvelle commande
			d) si c'est une redirections, on gere le fichier
				1) recupere le nom du fichier
				2) creation de la commande si necessaire
				3) ajout de la redirections
		D) Gestion des variables d'environnement
			a) extrait le nom de la varibale
			b) lit la variables (ou un seul digit si c'est "$1")
			c) ajout des token de type ENV_VAR
			d) ajout en arguments de la commande courante
					on traite '$VAR' comme un arguments
			(Pas de lookup reel, pas expansion
				=> on se contente de parser et stocker "VAR" ou "1" si c'est $1)
	3) Verification finale des tokens
		↘️
	2) fonctions d'affichage (DEBUG) et
	nettoyage (libere la liste de commandes)
*/

char	*ft_get_next_token_redir(const char **input)
{
	const char	*start;

	start = *input;
	while (**input && **input != ' ' && **input != '\t' && **input != '|'
		&& **input != '\"' && **input != '\'')
		(*input)++;
	return (ft_strndup(start, *input - start));
}

int	ft_handle_operators(t_parse_context *ctx)
{
	char	*file;

	if (!ft_handle_operator(ctx->head, ctx->input, ctx))
		return (0);
	if (**ctx->input == '|')
	{
		*ctx->current = ft_init_command(ctx->cmd_lst);
		if (!*ctx->current)
			return (ft_err_split_ope(*ctx->current, *ctx->head), 0);
	}
	if ((**ctx->input == '>' || **ctx->input == '<'))
	{
		file = ft_get_next_token(ctx->input);
		if (!file)
			return (ft_err_bad_redirec(*ctx->cmd_lst, *ctx->head), 0);
		if (!*ctx->current)
			*ctx->current = ft_init_command(ctx->cmd_lst);
		if (!ft_add_redirections_struct(*ctx->current,
				ft_identify_token((char *)(*ctx->input)), file, ctx))
			return (free(file), ft_err_split_ope(*ctx->cmd_lst, *ctx->head), 0);
		free(file);
	}
	return (1);
}

void	ft_let_go_split(t_parse_context ctx, int *last_exit_status)
{
	ft_free_commande_lst(*ctx.cmd_lst);
	ft_free_token(*ctx.head);
	*last_exit_status = ctx.exit_status;
}

int	finalize_ctx(t_parse_context *ctx, int *last_exit_status)
{
	if (!ft_valid_token(*ctx->head, ctx))
		return (*last_exit_status = ctx->exit_status, 0);
	ft_free_commande_lst(*ctx->cmd_lst);
	return (1);
}

int	ft_split_token(t_token **head, const char *input, t_env **env_cpy,
		int *last_exit_status)
{
	t_parse_context	ctx;
	t_command		*cmd_lst;
	t_command		*current;

	init_cmd_ctx(&ctx, &cmd_lst, &current);
	ctx.head = head;
	ctx.input = &input;
	ctx.input_exec = input;
	ctx.env_cpy = env_cpy;
	ctx.last_token = NULL;
	ctx.flag_heredoc = 0;
	init_cmd_ctx(&ctx, &cmd_lst, &current);
	ctx.exit_status = *last_exit_status;
	if (!ft_check_syntax(input, &ctx))
		return (*last_exit_status = ctx.exit_status, 0);
	if (!process_tokens(&ctx, last_exit_status))
		return (0);
	if (!finalize_ctx(&ctx, last_exit_status))
		return (0);
	*head = *ctx.head;
	*last_exit_status = 0;
	return (1);
}
