/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:38:44 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/16 08:38:45 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// /*
//     - Double quote non trouvée
//     - Sauter la quote ouvrante
//     - Parcourir jusqu'à la prochaine quote fermante ou caractère spécial
//     - Sauter les caractères échappés
//     - Gestion des variables d'environnement
//     -  Avancer jusqu'au `$`
//         - Réinitialiser après le traitement
//         - Réinitialiser le début
//     - Vérifier si une quote fermante est trouvée
//     - Concaténer les contenus si nécessaire
//     - Sauter la quote fermante
//     - Vérifier si une autre quote suit immédiatement
//     - Sauter l'ouverture de la prochaine quote
//     - Reprendre l'analyse
//     - Fin de l'analyse des quotes
// */

t_quote init_quote(void)
{
    return ((t_quote){0, 0, 0});
}

char *ft_extract_quotent(const char **input, t_quote *state)
{
    const char *start;
    size_t lenght;
    char *content;

    start = *input + state->start;
    lenght = 0;
    while (**input && !((state->in_single && start[lenght] == '\'') ||
                            (state->in_double && start[lenght] == '"')))
    {
        lenght++;
    }
    if (!start[lenght])
    {
        ft_printf_fd(STDERR_FILENO, "minishell: unclosed quotes detected\n");
        return (NULL);
    }
    content = ft_strndup(start + 1, lenght - 1);
    if (!content)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: memeory allocation failed\n");
        return (NULL);
    }
    state->start += lenght + 1;
    return (content);
}



static char *ft_handle_single_quote(const char **input)
{
    const char *start;
    size_t lenght;
    char *content;

    content = NULL;
    start = *(input)++;
    lenght = 0;
    while (start[lenght] && start[lenght] != '\'')
        lenght++;
    if (!start[lenght])
    {
        ft_printf_fd(STDERR_FILENO, "minishell: unclosed single quote\n");
        return (NULL);
    }
    content = ft_strndup(start, lenght);
    *input = start + lenght + 1;
    return (content);
}

static char *ft_handle_double_quote(const char **input, t_env **env_cpy)
{
    char *content;
    char *expendad;
    char *tmp;
    int i;

    i = 0;
    content = ft_extract_content(input, )

}



char *ft_handle_quote(const char **input, t_quote *state, t_env **env_cpy)
{
    char *content;

    content = NULL;
    if (**input == '\'' && !state->in_double)
    {
        state->in_single = !state->in_single;
        content = ft_handle_single_quote(input);
    }
    if (**input == '"' && !state->in_single)
    {
        state->in_double = !state->in_double;
        content = ft_handle_double_quote(input, env_cpy);
    }
    if (!content)
        return (NULL);
    return (content);
}
