/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:18 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/18 15:01:34 by dpascal          ###   ########.fr       */
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

// void	ft_handle_quotes(const char **input, t_token **head, t_command **cmd_lst, t_command **current, t_env **env_cpy)
// static int	ft_handle_operators(const char **input, t_token **head, t_command **cmd_lst, t_command **current)
// int	ft_handle_env_vars(const char **input, t_token **head, t_command **cmd_lst, t_command **current, t_env **env_cpy)

// void	ft_handle_quotes(t_parse_context *ctx)
// {
// 	char	*token_value;

// 	token_value = ft_handle_quote(ctx);
// 	if (!token_value)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "minishell: error: invalid quoted string\n");
// 		return (ft_err_split(*ctx->cmd_lst, *ctx->head));
// 	}
// 	ft_add_token(ctx->head, ft_create_token(TOKEN_WORD, token_value));
// 	if (!*ctx->current)
// 		*ctx->current = ft_init_command(ctx->cmd_lst);
// 	if (!ft_add_arguments(*ctx->current, token_value))
// 	{
// 		ft_printf_fd(STDERR_FILENO, "minishell: error: invalid quoted string\n");
// 		free(token_value);
// 		return (ft_err_split(*ctx->cmd_lst, *ctx->head));
// 	}
// 	free(token_value);
// }



// static int	ft_handle_operators(t_parse_context *ctx)
// {
//     char	*file;

// 	if (!ft_handle_operator(ctx->head, ctx->input))
// 		return (0);
// 	if (**ctx->input == '|')
// 	{
// 		*ctx->current = ft_init_command(ctx->cmd_lst);
// 		if (!*ctx->current)
// 			return (ft_err_split_ope(*ctx->current, *ctx->head), 0);
// 	}
// 	else if (**ctx->input == '>' || **ctx->input == '<')
// 	{
// 		file = ft_get_next_token(ctx->input);
// 		if (!file)
// 			return (ft_err_bad_redirec(*ctx->cmd_lst, *ctx->head), 0);
// 		if (!*ctx->current)
// 			*ctx->current = ft_init_command(ctx->cmd_lst);
// 		if (!ft_add_redirections_struct(*ctx->current, ft_identify_token((char *)(*ctx->input)), file))
// 		{
// 			ft_printf_fd(STDERR_FILENO, "minishell: error: failed to add redirection for file `%s`\n", file);
// 			free(file);
// 			return (ft_err_split_ope(*ctx->cmd_lst, *ctx->head), 0);
// 		}
// 		free(file);
// 	}
// 	return (1);
// }

// int	ft_handle_env_vars(t_parse_context *ctx)
// {
//     char	*var_name;
//     char	*var_value;

// 	var_name = ft_extract_env_var(ctx->input);
// 	if (!var_name)
// 		return(ft_printf_fd(STDERR_FILENO, "minishell: error: invalid environment variable name\n"), 0);
// 	if (ft_strcmp(var_name, "$$") == 0)
// 	{
// 		free(var_name);
// 		var_value = ft_get_pid_str();
// 	}
// 	else
// 	{
// 		var_value = print_node_by_key(ctx->env_cpy, var_name);
// 		free(var_name);
// 	}
// 	if (check_variable_backslash_n(var_value))
// 		var_value = replace_with_space(var_value);
// 	if (!var_value)
// 		return(ft_printf_fd(STDERR_FILENO, "minishell: invalid environment variable\n"), 0);
// 	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
// 	if (!*ctx->current)
// 		*ctx->current = ft_init_command(ctx->cmd_lst);
// 	if (!ft_add_arguments(*ctx->current, var_value))
// 		return(ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"), free(var_value), 0);
// 	return (1);
// }

// int	ft_handle_words(t_parse_context *ctx)
// {
// 	char	*token_value;

// 	token_value = ft_get_next_token(ctx->input);
// 	if (token_value && *token_value != '\0')
// 	{
// 		ft_add_token(ctx->head, ft_create_token(TOKEN_WORD, token_value));
// 		if (!*ctx->current)
// 			*ctx->current = ft_init_command(ctx->cmd_lst);
// 		if (!ft_add_arguments(*ctx->current, token_value))
// 		{
// 			ft_printf_fd(STDERR_FILENO, "minishell: error: failed to add argument `%s`\n", token_value);
// 			free(token_value);
// 			return (0);
// 		}
// 	}
// 	free(token_value);
// 	return (1);
// }

// int	ft_split_token(t_token **head, const char *input, t_env **env_cpy)
// {
// 	t_parse_context ctx;
// 	t_command *cmd_lst = NULL;
// 	t_command *current = NULL;

// 	ctx.cmd_lst = &cmd_lst;
// 	ctx.current = &current;
// 	ctx.head = head;
// 	ctx.input = &input;
// 	ctx.input_exec = input;
// 	ctx.env_cpy = env_cpy;
// 	if (!ft_check_syntax(input))
// 		return (0);
// 	while (**ctx.input)
// 	{
// 		if (**ctx.input == ' ' || **ctx.input == '\t')
// 			(*ctx.input)++;
// 		else if (**ctx.input == '\'' || **ctx.input == '"')
// 		{
// 			ft_handle_quotes(&ctx);
// 			if (!ctx.current)
// 				return (0);
// 		}
// 		else if (**ctx.input == '|' || **ctx.input == '>' || **ctx.input == '<')
// 		{
// 			if (!ft_handle_operators(&ctx))
// 				return (0);
// 		}
// 		else if (**ctx.input == '$')
// 		{
// 			if (!ft_handle_env_vars(&ctx))
// 				return (0);
// 		}
// 		else
// 		{
// 			if (!ft_handle_words(&ctx))
// 				return (0);
// 		}
// 	}
// 	if (ft_valid_token(*ctx.head) == 0)
// 	{
// 		ft_printf_fd(STDERR_FILENO, "minishell: syntax error in token list\n");
// 		return (0);
// 	}
// 	*head = *ctx.head;
// 	return (1);
// }









void ft_handle_quotes(t_parse_context *ctx)
{
	char *quote_content;
	const char *input_ptr;
	char prev_char;
	char *new;

	input_ptr = *ctx->input;
	quote_content = ft_handle_quote(ctx);
	if (!quote_content)
		return (ft_err_split(*ctx->cmd_lst, *ctx->head));
	if (input_ptr > ctx->input_exec)
		prev_char = *(input_ptr - 1); // (*input)
	else
		prev_char = ' ';
	if (!ft_isspace(prev_char) && ctx->last_token && ctx->last_token->value)
	{
		new = ft_strjoin_free(ctx->last_token->value, quote_content);
		if (!new)
		{
			free(quote_content);
			ft_err_split(*ctx->cmd_lst, *ctx->head);
			return;
		}
		ctx->last_token->value = new;
		if (!ft_add_arguments(*ctx->current, quote_content))
		{
			// ft_printf_fd(2, "minishell: adding arguments error\n");
			free(quote_content);
			ft_err_split(*ctx->cmd_lst, *ctx->head);
			return;
		}
		free(quote_content);
		return;
	}
	ft_add_token(ctx->head, ft_create_token(TOKEN_WORD, quote_content));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->cmd_lst, quote_content))
	{
		// ft_printf_fd
		ft_err_split(*ctx->cmd_lst, *ctx->head);
		free(quote_content);
		return;
	}
	ctx->last_token = ft_last_token(*ctx->head);
	free(quote_content);
}

// void ft_handle_quotes(t_parse_context *ctx)
// {
//     char *quoted_content;
// 	size_t len;

// 	(void)len;
//     quoted_content = ft_handle_quote(ctx);
//     if (!quoted_content)
//     {
//         // ft_printf_fd(STDERR_FILENO, "minishell: error: invalid quoted string\n");
//         ft_err_split(*ctx->cmd_lst, *ctx->head);
//         return;
//     }
//     if (ctx->last_token && ctx->last_token->value)
//     {
//         len = ft_strlen(ctx->last_token->value);
//         if (len > 0 && !ft_isspace(ctx->last_token->value[len - 1]))
//         {
//             char *new_value = ft_strjoin_free(ctx->last_token->value, quoted_content);
//             if (!new_value)
//             {
//                 // ft_printf_fd(STDERR_FILENO, "minishell: error: allocation failed during concatenation\n");
//                 free(quoted_content);
//                 ft_err_split(*ctx->cmd_lst, *ctx->head);
//                 return;
//             }
//             ctx->last_token->value = new_value;
//             if (!ft_add_arguments(*ctx->current, quoted_content))
//             {
//                 ft_printf_fd(STDERR_FILENO, "minishell: error: failed to add quoted argument\n");
//                 free(quoted_content);
//                 ft_err_split(*ctx->cmd_lst, *ctx->head);
//                 return;
//             }
//             free(quoted_content);
//             return;
//         }
//     }
//     ft_add_token(ctx->head, ft_create_token(TOKEN_WORD, quoted_content));
//     if (!*ctx->current)
//         *ctx->current = ft_init_command(ctx->cmd_lst);
//     if (!ft_add_arguments(*ctx->current, quoted_content))
//     {
//         ft_printf_fd(STDERR_FILENO, "minishell: error: failed to add argument `%s`\n", quoted_content);
//         free(quoted_content);
//         ft_err_split(*ctx->cmd_lst, *ctx->head);
//         return;
//     }
//     ctx->last_token = ft_last_token(*ctx->head);
//     free(quoted_content);
// }

int	ft_handle_operators(t_parse_context *ctx)
{
    char	*file;

	if (!ft_handle_operator(ctx->head, ctx->input))
		return (0);
	if (**ctx->input == '|')
	{
		*ctx->current = ft_init_command(ctx->cmd_lst);
		if (!*ctx->current)
			return (ft_err_split_ope(*ctx->current, *ctx->head), 0);
	}
	else if (**ctx->input == '>' || **ctx->input == '<')
	{
		file = ft_get_next_token(ctx->input);
		if (!file)
			return (ft_err_bad_redirec(*ctx->cmd_lst, *ctx->head), 0);
		if (!*ctx->current)
			*ctx->current = ft_init_command(ctx->cmd_lst);
		if (!ft_add_redirections_struct(*ctx->current, ft_identify_token((char *)(*ctx->input)), file))
		{
			ft_printf_fd(STDERR_FILENO, "minishell: error: failed to add redirection for file `%s`\n", file);
			free(file);
			return (ft_err_split_ope(*ctx->cmd_lst, *ctx->head), 0);
		}
		free(file);
	}
	return (1);
}

int	ft_handle_env_vars(t_parse_context *ctx)
{
    char	*var_name;
    char	*var_value;

	var_name = ft_extract_env_var(ctx->input);
	if (!var_name)
		return(ft_printf_fd(STDERR_FILENO, "minishell: error: invalid environment variable name\n"), 0);
	if (ft_strcmp(var_name, "$$") == 0)
	{
		free(var_name);
		var_value = ft_get_pid_str();
	}
	var_value = print_node_by_key(ctx->env_cpy, var_name);
	if (!var_value)
		return (0);
	if (check_variable_backslash_n_parse(var_value) == 1)
	{
		printf("1\n");
		var_value = replace_with_space_parse(var_value);
	}
	if (!var_value)
		return(0);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));	
	free(var_name);
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
		return(ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"), free(var_value), 0);
	// free(var_value);
	return (1);
}

int	ft_handle_words(t_parse_context *ctx)
{
	char	*token_value;
	t_token *new_token;

	token_value = ft_get_next_token(ctx->input);
	if (token_value && *token_value != '\0')
	{
		new_token = ft_create_token(TOKEN_WORD, token_value);
		ft_add_token(ctx->head, new_token);
		ctx->last_token = new_token;
		if (!*ctx->current)
			*ctx->current = ft_init_command(ctx->cmd_lst);
		if (!ft_add_arguments(*ctx->current, token_value))
		{
			// ft_printf_fd(STDERR_FILENO, "minishell: error: failed to add argument `%s`\n", token_value);
			free(token_value);
			return (0);
		}
	}
	free(token_value);
	return (1);
}

int	ft_split_token(t_token **head, const char *input, t_env **env_cpy)
{
	t_parse_context ctx;
	t_command *cmd_lst = NULL;
	t_command *current = NULL;

	ctx.cmd_lst = &cmd_lst;
	ctx.current = &current;
	ctx.head = head;
	ctx.input = &input;
	ctx.input_exec = input;
	ctx.env_cpy = env_cpy;
	ctx.exit_status = 0;
	ctx.last_token = NULL;
	// ft_init_cmd(cmd_lst, current, ctx);
	// ft_init_ctx(head, input, env_cpy, ctx);
	if (!ft_check_syntax(input, &ctx))
	{
		exit(ctx.exit_status);
		// return (ctx.exit_status);
	}
	while (**ctx.input)
	{
		if (**ctx.input == ' ' || **ctx.input == '\t')
			(*ctx.input)++;
		else if (**ctx.input == '\'' || **ctx.input == '"')
			ft_handle_quotes(&ctx);
		else if (**ctx.input == '|' || **ctx.input == '>' || **ctx.input == '<')
		{
			if (!ft_handle_operators(&ctx))
				return (0);
		}
		else if (**ctx.input == '$')
		{
			if (!ft_handle_env_vars(&ctx))
				return (ft_printf("\n"), 0);
		}
		else
		{
			if (!ft_handle_words(&ctx))
				return (0);
		}
	}
	if (!ft_valid_token(*ctx.head))
		return (0);
	*head = *ctx.head;
	return (1);
}

















// void	ft_split_token(t_token **head, const char *input)
// {
// 			char *var_name;

// 	t_command *cmd_lst = NULL; // Liste des commandes
// 	t_command *current = NULL; // Commande courante
// 	char *token_value;         // Buffer pour stocker un mot/quote/env var
// 	char *file;                // Buffer pour stocker un fichier de redirection
// 	// 1) Vérification de la syntaxe globale
// 	if (!ft_check_syntax(input))
// 		return ;
// 	// 2) Parcours de la chaîne d'entrée
// 	while (*input)
// 	{
// 		// a) Ignorer les espaces et tabulations
// 		if (*input == ' ' || *input == '\t')
// 		{
// 			input++;
// 			continue ;
// 		}
// 		// b) Gestion des quotes
// 		else if (*input == '\'' || *input == '\"')
// 		{
// 			token_value = ft_handle_quote(&input, *input);
// 			if (!token_value)
// 			{
// 				ft_error_quote();
// 				ft_free_token(*head);
// 				*head = NULL;
// 				ft_free_commande_lst(cmd_lst);
// 				return ;
// 			}
// 			// Ajout du token de type WORD (même si c'est issu de quotes)
// 			ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
// 			// Création de commande si nécessaire, puis ajout en arguments
// 			if (!current)
// 				current = ft_init_command(&cmd_lst);
// 			if (!ft_add_arguments(current, token_value))
// 			{
// 				ft_printf("[ERROR] Impossible d'ajouter l'argument : %s\n",
// 					token_value);
// 				ft_free_token(*head);
// 				*head = NULL;
// 				ft_free_commande_lst(cmd_lst);
// 				return ;
// 			}
// 		}
// 		// c) Gestion des opérateurs (pipes, redirections)
// 		else if (*input == '|' || *input == '>' || *input == '<')
// 		{
// 			// Appel à la fonction auxiliaire pour créer le token correspondant
// 			ft_handle_operator(head, &input);
// 			if (*head == NULL) // Erreur signalée par ft_handle_operator
// 				return ;
// 			// Si c'est un pipe, on crée une nouvelle commande
// 			if (*(input - 1) == '|')
// 			{
// 				current = ft_init_command(&cmd_lst);
// 				if (!current)
// 				{
// 					ft_printf("[ERROR] Échec de création de commande\n");
// 					ft_free_token(*head);
// 					*head = NULL;
// 					ft_free_commande_lst(cmd_lst);
// 					return ;
// 				}
// 			}
// 			// Si c'est une redirection, on gère le fichier
// 			else if (*(input - 1) == '>' || *(input - 1) == '<')
// 			{
// 				// Récupérer le fichier (mot suivant)
// 				file = ft_get_next_token(&input);
// 				if (!file)
// 				{
// 					ft_printf("[ERROR] Redirection sans fichier valide\n");
// 					ft_free_token(*head);
// 					*head = NULL;
// 					ft_free_commande_lst(cmd_lst);
// 					return;
// 				}
// 				// Création de commande si nécessaire
// 				if (!current)
// 					current = ft_init_command(&cmd_lst);
// 				// Ajout de la redirection
// 				if (!ft_add_redirections_struct(current,
// 						ft_identify_token((char *)(input - 1)), file))
// 				{
// 					ft_printf("[ERROR] Échec de l'ajout de la redirection : %s\n", file);
// 					ft_free_token(*head);
// 					*head = NULL;
// 					ft_free_commande_lst(cmd_lst);
// 					return;
// 				}
// 			}
// 		}
// 		// d) Gestion des variables d'environnement
// 		else if (*input == '$') // Gestion des variables d'environnement
// 		{
// 			// 1) Extraire le nom de la variable
// 			var_name = ft_extract_env_var(&input);
// 			// └─ Avance le *input,
// 			// lit la variable (ou un seul digit si c'est `$1`)
// 			if (!var_name)
// 			{
// 				ft_printf("[ERROR] Variable d'environnement invalide\n");
// 				ft_free_token(*head);
// 				*head = NULL;
// 				ft_free_commande_lst(cmd_lst);
// 				return ;
// 			}
// 			// 2) Créer un token ENV_VAR (ou WORD) avec ce nom brut
// 			ft_add_token(head, ft_create_token(TOKEN_ENV_VAR, var_name));
// 			// 3) Optionnel : Ajout en argument de la commande courante
// 			//    Si vous traitez `$VAR` comme un argument
// 			if (!current)
// 				current = ft_init_command(&cmd_lst);
// 			if (!ft_add_arguments(current, var_name))
// 			{
// 				ft_printf("[ERROR] Impossible d'ajouter la variable en argument : %s\n", var_name);
// 				ft_free_token(*head);
// 				*head = NULL;
// 				ft_free_commande_lst(cmd_lst);
// 				return ;
// 			}
// 			// Pas de lookup réel, pas d'expansion
// 			// => On se contente de parser et de stocker "VAR" ou "1" si c'est `$1`.
// 		}
// 		// e) Gestion des mots (commandes/arguments génériques)
// 		else
// 		{
// 			token_value = ft_get_next_token(&input);
// 			if (token_value && *token_value != '\0')
// 			{
// 				ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
// 				if (!current)
// 					current = ft_init_command(&cmd_lst);
// 				if (!ft_add_arguments(current, token_value))
// 				{
// 					ft_printf("[ERROR] Impossible d'ajouter l'argument : %s\n",
// 						token_value);
// 					ft_free_token(*head);
// 					*head = NULL;
// 					ft_free_commande_lst(cmd_lst);
// 					return ;
// 				}
// 			}
// 		}
// 		input++;
// 	}
// 	// 3) Vérification finale des tokens
// 	if (!ft_valid_token(*head))
// 	{
// 		ft_printf("[ERROR] Tokens invalides\n");
// 		ft_free_token(*head);
// 		*head = NULL;
// 		ft_free_commande_lst(cmd_lst);
// 		return ;
// 	}
// 	// 4) Affichage et nettoyage
// 	ft_print_tokens(*head);
// 	ft_print_command_lst(cmd_lst);
// 	ft_free_commande_lst(cmd_lst);
// }

