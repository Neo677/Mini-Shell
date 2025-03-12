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

char	*ft_handle_single_quote(const char **input, t_parse_context *ctx)
{
	const char	*start;
	char		*content;
	size_t		i;

	content = NULL;
	i = 0;
	if (**input != '\'')
		return (NULL);
	start = ++(*input);
	while ((*input)[i] && (*input)[i] != '\'')
		i++;
	if ((*input)[i] != '\'')
	{
		content = ft_eof_single_quote(ctx);
		if (!content)
			return (NULL);
		(*input) += i + 1;
		return (content);
	}
	content = ft_strndup(start, i);
	if (!content)
		return (NULL);
	(*input) += i + 1;
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
