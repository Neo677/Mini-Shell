/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:18 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:19 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_handle_quotes(const char **input, t_token **head, t_command **cmd_lst, t_command **current)
{
    char *token_value;
    
    token_value = ft_handle_quote(input, **input);
    if (!token_value)
    {
        ft_error_quote();
        ft_free_token(*head);
        *head = NULL;
        ft_free_commande_lst(*cmd_lst);
        return;
    }

    ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));

    if (!*current)
        *current = ft_create_command(cmd_lst);

    if (!ft_add_arguments(*current, token_value))
    {
        ft_printf("[ERROR] Impossible d'ajouter l'argument : %s\n", token_value);
        ft_free_token(*head);
        *head = NULL;
        ft_free_commande_lst(*cmd_lst);
        return;
    }
}

void ft_handle_operators(const char **input, t_token **head, t_command **cmd_lst, t_command **current)
{
    char *file;

    ft_handle_operator(head, input);
    if (*head == NULL) // Erreur signale par handle_operator
        return;

    if (*(input[-1]) == '|') // pipe : nouvelle commande
    {
        *current = ft_create_command(cmd_lst);
        if (!*current)
        {
            ft_printf("[ERROR] Échec de création de commande\n");
            ft_free_token(*head);
            *head = NULL;
            ft_free_commande_lst(*cmd_lst);
            return;
        }
    }
    else if (*(input[-1]) == '>' || *(input[-1]) == '<') // redrirec
    {
        file = ft_get_next_token(input);
        if (!file)
        {
            ft_printf("[ERROR] Redirection sans fichier valide\n");
            ft_free_token(*head);
            *head = NULL;
            ft_free_commande_lst(*cmd_lst);
            return;
        }

        if (!*current)
            *current = ft_create_command(cmd_lst);

        if (!ft_add_redirections_struct(*current, ft_identify_token((char *)(*input - 1)), file))
        {
            ft_printf("[ERROR] Échec de l'ajout de la redirection : %s\n", file);
            ft_free_token(*head);
            *head = NULL;
            ft_free_commande_lst(*cmd_lst);
            return;
        }
    }
}

void ft_handle_env_vars(const char **input, t_token **head, t_command **cmd_lst, t_command **current)
{
    char *var_name;
    
    var_name = ft_extract_env_var(input);
    if (!var_name)
    {
        ft_printf("[ERROR] Variable d'environnement invalide\n");
        ft_free_token(*head);
        *head = NULL;
        ft_free_commande_lst(*cmd_lst);
        return;
    }
    ft_add_token(head, ft_create_token(TOKEN_ENV_VAR, var_name));

    if (!*current)
        *current = ft_create_command(cmd_lst);
    if (!ft_add_arguments(*current, var_name))
    {
        ft_printf("[ERROR] Impossible d'ajouter la variable en argument : %s\n", var_name);
        ft_free_token(*head);
        *head = NULL;
        ft_free_commande_lst(*cmd_lst);
        return;
    }
}

void ft_handle_words(const char **input, t_token **head, t_command **cmd_lst, t_command **current)
{
    char *token_value;
    
    token_value = ft_get_next_token(input);
    if (token_value && *token_value != '\0')
    {
        ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));

        if (!*current)
            *current = ft_create_command(cmd_lst);

        if (!ft_add_arguments(*current, token_value))
        {
            ft_printf("[ERROR] Impossible d'ajouter l'argument : %s\n", token_value);
            ft_free_token(*head);
            *head = NULL;
            ft_free_commande_lst(*cmd_lst);
            return;
        }
    }
}

void ft_split_token(t_token **head, const char *input)
{
    t_command *cmd_lst;// Liste des commandes
    t_command *current;// Commande courante

    cmd_lst = NULL;
    current = NULL;
    if (!ft_check_syntax(input))
        return;
    while (*input)
    {
        if (*input == ' ' || *input == '\t')
            input++; // Ignore les espaces
        else if (*input == '\'' || *input == '\"')
            ft_handle_quotes(&input, head, &cmd_lst, &current);
        else if (*input == '|' || *input == '>' || *input == '<')
            ft_handle_operators(&input, head, &cmd_lst, &current);
        else if (*input == '$')
            ft_handle_env_vars(&input, head, &cmd_lst, &current);
        else
            ft_handle_words(&input, head, &cmd_lst, &current);
    }
    if (!ft_valid_token(*head))
        ft_free_split(*head, cmd_lst);
    ft_free_commande_lst(cmd_lst);
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
// 			// Ajout du token de type WORD (même si c’est issu de quotes)
// 			ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
// 			// Création de commande si nécessaire, puis ajout en arguments
// 			if (!current)
// 				current = ft_create_command(&cmd_lst);
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
// 				current = ft_create_command(&cmd_lst);
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
// 					current = ft_create_command(&cmd_lst);
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
// 			// lit la variable (ou un seul digit si c’est `$1`)
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
// 				current = ft_create_command(&cmd_lst);
// 			if (!ft_add_arguments(current, var_name))
// 			{
// 				ft_printf("[ERROR] Impossible d'ajouter la variable en argument : %s\n", var_name);
// 				ft_free_token(*head);
// 				*head = NULL;
// 				ft_free_commande_lst(cmd_lst);
// 				return ;
// 			}
// 			// Pas de lookup réel, pas d'expansion
// 			// => On se contente de parser et de stocker "VAR" ou "1" si c’est `$1`.
// 		}
// 		// e) Gestion des mots (commandes/arguments génériques)
// 		else
// 		{
// 			token_value = ft_get_next_token(&input);
// 			if (token_value && *token_value != '\0')
// 			{
// 				ft_add_token(head, ft_create_token(TOKEN_WORD, token_value));
// 				if (!current)
// 					current = ft_create_command(&cmd_lst);
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
// 	ft_print_tokens(*head); // Debug : affiche la liste de tokens
// 	// ft_print_command_lst(cmd_lst); // Debug : affiche les commandes (args, redirs, etc.)
// 	ft_free_commande_lst(cmd_lst); // Libère la liste de commandes
// }

