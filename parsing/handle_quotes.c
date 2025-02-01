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

char *ft_strjoin_free(char *s1, char *s2)
{
    char *new_str;

    if (!s1 || !s2)
    {
        free(s1);
        free(s2);
        return (NULL);
    }
    new_str = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (new_str);
}

char *ft_strjoin_char(char *str, char c)
{
    char    *new;
    int     len;

    if (!str)
    {
        new = malloc(2);
        if (!new)
            return (NULL);
        new[0] = c;
        new[1] = '\0';
        return (new);
    }
    len = ft_strlen(str);
    new = malloc(len + 2);
    if (!new)
        return (NULL);
    ft_memcpy(new, str, len);
    new[len] = c;
    new[len + 1] = '\0';
    free(str);
    return (new);
}

int ft_get_var_len(const char *str)
{
    int len;

    len = 1;
    if (str[1] == '?')
        return (2);
    if (!ft_isalpha(str[1]) && str[1] != '_')
        return (1);
    while (str[len] && (ft_isalnum(str[len]) || str[len] == '_'))
        len++;
    return (len);
}

char *ft_get_env(char *name, t_env **env_cpy)
{
    t_env *tmp;

    tmp = *env_cpy;
    while (tmp)
    {
        if (ft_strcmp2(tmp->key, name) == 0)
            return (tmp->value);
        tmp = tmp->next;
    }
    return (NULL);
}

char *ft_get_var_value(const char *var_str, t_env **env_cpy, int exit_status)
{
    char *var_name;
    char *value;
    int len;

    len = ft_get_var_len(var_str);
    if (var_str[1] == '?')
        return (ft_itoa(exit_status));
    var_name = ft_strndup(var_str + 1, len - 1);
    if (!var_name)
        return (NULL);
    value = ft_get_env(var_name, env_cpy);
    if (!value)
        return (ft_strdup(""));
    return (ft_strdup(value));
}

char *ft_expand_env_var(char *content, t_env **env_cpy, int exit_satus)
{
    char *result;
    char *tmp;
    int i;
    int var_len;

    result = ft_strdup("");
    i = 0;
    while (content[i])
    {
        if (content[i] == '$' && (i == 0 || content[i - 1] != '\\'))
        {
            var_len = ft_get_var_len(content + i);
            tmp = ft_get_var_value(content + i, env_cpy, exit_satus);
            result = ft_strjoin_free(result, tmp);
            i += var_len;
            free(tmp);
        }
        else
        {
            result = ft_strjoin_char(result, content[i]);
            i++;
        }
    }
    free(content);
    return (result);
}

t_quote init_quote(int exit_status)
{
    return ((t_quote){0, 0, exit_status, 0});
}

char *ft_handle_single_quote(const char **input, t_quote *state)
{
    const char *start;
    char *content;
    size_t size;

    state->in_single = 1;
    start = ++(*input);
    size = 0;
    while (start[size] && start[size] != '\'')
        size++;
    if (!start[size])
    {
        ft_printf_fd(STDERR_FILENO, "minishell: unclosed single quote\n");
        state->in_single = 0;
        return (NULL);
    }
    content = ft_strndup(start, size);
    *input = start + size + 1;
    state->in_single = 0;
    return (content);
}

char *ft_handle_double_quote(const char **input, t_quote *state, t_env **env_cpy)
{
    const char *start;
    char *content;
    size_t size;
    char *expanded;

    state->in_double = 1;
    start = ++(*input);
    size = 0;
    while (start[size] && start[size] != '"')
    {
        if (start[size] == '\\' && 
            (start[size + 1] == '"' || start[size + 1] == '\\' || start[size + 1] == '$'))
        {
            size++;
        }
        size++;
    }
    if (!start[size])
    {
        ft_printf_fd(STDERR_FILENO, "minishell: unclosed double quote\n");
        state->in_double = 0;
        return (NULL);
    }
    content = ft_strndup(start, size);
    expanded = ft_expand_env_var(content, env_cpy, state->exit_status);
    free(content);
    *input = start + size + 1;
    state->in_double = 0;
    return (expanded);
}

char *ft_handle_quote(const char **input, t_quote *state, t_env **env_cpy)
{
    if (**input == '\'' && !state->in_double)
        return (ft_handle_single_quote(input, state));
    else if (**input == '"' && !state->in_single)
        return (ft_handle_double_quote(input, state, env_cpy));
    return (NULL);
}