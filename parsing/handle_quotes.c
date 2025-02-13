/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 08:38:44 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/13 02:28:05 by dpascal          ###   ########.fr       */
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

char	*ft_extract_quotent(const char *start, size_t len)
{
	char	*tmp;

	tmp = ft_strndup(start, len);
	if (!tmp)
	{
		ft_printf_fd(STDERR_FILENO, "minishell: error memory allocation failed\n");
		return (NULL);
	}
	return (tmp);
}

char	*ft_concatent_content(char *content, char *tmp)
{
	char	*new;

	if (content)
	{
		new = ft_strjoin_v2(content, tmp);
		free(content);
		free(tmp);
		if (!new)
		{
			ft_printf_fd(STDERR_FILENO, "minishell: error allocation failed during concatenation\n");
			return (NULL);
		}
		return (new);
	}
	return (tmp);
}

int	ft_update_ptr_input(const char **input, size_t *i, const char **start)
{
	(*input) += *i + 1;
	if (**input == '\"')
	{
		(*input)++;
		*start = *input;
		*i = 0;
		return (1);
	}
	return (0);
}

char    *ft_strjoin_free(char *s1, char *s2)
{
    char    *result;
    
    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
        
    result = ft_strjoin(s1, s2);
    free(s1);
    free(s2);
    return (result);
}

char    *ft_eof_quote(const char *input, t_parse_context *ctx)
{
    char    *line;
    char    *new_str;
    char    *new_str2;
    char    *history;
    char    **test;

    (void)input;
    new_str = NULL;
    new_str2 = ft_strdup_v2(ctx->input_exec);
    while (1)
    {
        line = readline("> ");
        if (line == NULL)
        {
            ft_printf_fd(2, "bash: unexpected EOF while looking for matching `\"'");
            free(line);
            free(new_str);
            return (NULL);
        }
        if (ft_strcmp2(line, "\"") == 0)
        {
            free(line);
            break ;
        }
        new_str = ft_strjoin(new_str, "\n");
        new_str = ft_strjoin(new_str, line);
    }
    new_str = ft_strjoin(new_str, "\n");
    history = ft_strjoin(new_str2, new_str);
    test = ft_split_built(history, '"');
    add_history(history);
    // printf ("new_str = %s\n", test[1]);
    // free(history);
    return (test[1]);
}

char    *replace_with_space(char *str)
{
    char    *new_str;
    int i;
    int j;

    new_str = malloc(sizeof(char)* ft_strlen(str) + 1);
    if (!new_str)
        return (str);
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '\n')
            new_str[j] = ' ';
        else  
            new_str[j] = str[i];
        i++;
        j++;
    }
    new_str[j] = '\0';
    printf("new_str sans space = %s\n", new_str);
    return (new_str);
}

static char *ft_handle_double_quote(const char **input, t_parse_context *ctx) 
{
    const char *start;
    char *content;
    char *tmp;
    size_t i;

    content = NULL;
    i = 0;
    if (**input != '\"')
        return (NULL);
    start = ++(*input);
    while ((*input)[i] && (*input)[i] != '\"')
    {
        if ((*input)[i] == '$')
        {
            tmp = ft_extract_quotent(start, i);
            content = ft_concatent_content(content, tmp);
            if (!content)
                return (NULL);
            if (!ft_handle_env_vars(ctx))
                return (NULL);
            start = *input;
            i = 0;
        }
        else
            i++;
    }
    if ((*input)[i] != '\"')
    {
        char    *test;
        test = ft_eof_quote(*input, ctx);
        // printf("input = %s\n", *input);
        if (!test)
            return (NULL);
        // tmp = ft_extract_quotent(start, i);
        content = ft_concatent_content(content, test);
        if (!content)
            return (NULL);
        (*input) += i + 1;
        return (content);
        // return (test);
        // ft_printf_fd(STDERR_FILENO, "minishell: syntax error: unclosed doule quote\n");
        // while (1)
        // {
            
            // *input = readline("> ");
            
        // }
        // return (NULL);
    }
    tmp = ft_extract_quotent(start, i);
    content = ft_concatent_content(content, tmp);
    if (!content)
        return (NULL);
    (*input) += i + 1;
    return (content);
}

static char *ft_handle_single_quote(const char **input) 
{
    const char *start;
    char *content;
    size_t i;

    i = 0;
    if (**input != '\'')
        return (NULL);
    start = ++(*input);
    while ((*input)[i] && (*input)[i] != '\'')
        i++;
    if ((*input)[i] != '\'')
    {
        ft_printf_fd(STDERR_FILENO, "minishell: syntax error: unclosed single quote\n");
        return (NULL);
    }
    content = ft_strndup(start, i);
    if (!content)
    {
        ft_printf_fd(STDERR_FILENO, "minishell: error: memory allocation failed in ft_handle_single_quote\n");
        return (NULL);
    }
    (*input) += i + 1;
    return (content);
}

char *ft_handle_quote(t_parse_context *ctx) 
{
    char *content = NULL;

    if (**ctx->input == '\'') 
    {
        content = ft_handle_single_quote(ctx->input);
    } 
    else if (**ctx->input == '\"')
    {
        content = ft_handle_double_quote(ctx->input, ctx);
    }
    if (!content) 
    {
        ft_printf_fd(STDERR_FILENO, "minishell: error while processing quotes\n");
        return (NULL);
    }
    return (content);
}
