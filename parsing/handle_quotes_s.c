/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_s.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:32:31 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:32:32 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	- Double quote non trouvée
	- Sauter la quote ouvrante
	- Parcourir jusqu'à la prochaine quote fermante ou caractère spécial
	- Sauter les caractères échappés
	- Gestion des variables d'environnement
	-  Avancer jusqu'au `$`
		- Réinitialiser après le traitement
		- Réinitialiser le début
	- Vérifier si une quote fermante est trouvée
	- Concaténer les contenus si nécessaire
	- Sauter la quote fermante
	- Vérifier si une autre quote suit immédiatement
	- Sauter l'ouverture de la prochaine quote
	- Reprendre l'analyse
	- Fin de l'analyse des quotes
*/

static char	*append_char_to_result(char *result, char c)
{
	char	letter[2];
	char	*tmp;

	letter[0] = c;
	letter[1] = '\0';
	tmp = result;
	result = ft_strjoin(tmp, letter);
	free(tmp);
	return (result);
}

char	*ft_missing_quote(char *content)
{
	char	*tmp;
	char	*combined;

	tmp = ft_eof_single_quote();
	if (!tmp)
		return (free(content), NULL);
	combined = ft_strjoin(content, tmp);
	if (!combined)
		return (free(combined), free(tmp), NULL);
	free(content);
	free(tmp);
	return (combined);
}

char	*ft_handle_single_quote(const char **input, t_parse_context *ctx)
{
	char	*content;

	(void)ctx;
	if (**input != '\'')
		return (NULL);
	(*input)++;
	content = ft_strdup("");
	if (!content)
		return (NULL);
	while (**input && **input != '\'')
	{
		content = append_char_to_result(content, **input);
		if (!content)
			return (NULL);
		(*input)++;
	}
	if (**input == '\'')
		(*input)++;
	else
		content = ft_missing_quote(content);
	return (content);
}

char	*ft_handle_quote(t_parse_context *ctx)
{
	char	*content;

	if (!ctx || !ctx->input || !(*ctx->input))
	{
		ft_printf_fd(2,
			"minishell: unexpected end of input while processing quote\n");
		return (NULL);
	}
	if (**ctx->input == '\'')
		content = ft_handle_single_quote(ctx->input, ctx);
	else if (**ctx->input == '\"')
		content = ft_handle_double_quote(ctx->input, ctx);
	else
		content = NULL;
	if (!content)
	{
		if (!(*ctx->input) || **ctx->input == '\0')
			ft_printf_fd(2,
				"minishell: unexpected EOF while processing quote\n");
		else
			ft_printf_fd(2, "\n");
		return (NULL);
	}
	return (content);
}
