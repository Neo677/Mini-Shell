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

char    *ft_eof_double_quote(const char *input, t_parse_context *ctx)
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
            ft_printf_fd(2, "bash: unexpected EOF while looking for matching `\"'\n");
            free(line);
            free(new_str);
            return (NULL);
        }
        if (ft_strcmp(line, "\"") == 0)
        {
            free(line);
            break ;
        }
        new_str = ft_strjoin(new_str, "\n"); // leak here 
        new_str = ft_strjoin(new_str, line); // leak here 
    
/*        line = readline("> ");
        // ... error checking ...
        
        // Fix for newline addition
        char *tmp = new_str;
        new_str = ft_strjoin(tmp, "\n");
        free(tmp);
        
        // Fix for line addition
        tmp = new_str;
        new_str = ft_strjoin(tmp, line);
        free(tmp);
        free(line);
*/
    }
    new_str = ft_strjoin(new_str, "\n");
    history = ft_strjoin(new_str2, new_str);
    test = ft_split_built(history, '"');
    add_history(history);
    // printf ("new_str = %s\n", test[1]);
    // free(history);
    return (test[1]);
}

static int	ft_handle_env_vars_quote(t_parse_context *ctx)
{
    char	*var_name;
    char	*var_value;
	// char	*tmp;

	var_name = ft_extract_env_var(ctx->input);
	if (!var_name)
		return(ft_printf_fd(STDERR_FILENO, "minishell: error: invalid environment variable name\n"), 0);
	if (ft_strcmp(var_name, "$$") == 0)
	{
		free(var_name);
		var_value = ft_get_pid_str();
	}
	else
		var_value = print_node_by_key(ctx->env_cpy, var_name);
	if (!var_value)
		return(ft_printf_fd(STDERR_FILENO, "minishell: syntax error near unexpected token `|'\n"), 0);
	ft_add_token(ctx->head, ft_create_token(TOKEN_ENV_VAR, var_value));
	if (!*ctx->current)
		*ctx->current = ft_init_command(ctx->cmd_lst);
	if (!ft_add_arguments(*ctx->current, var_value))
		return(ft_printf_fd(STDERR_FILENO, "minishell: unbound variable\n"), free(var_value), 0);
	// free(var_value);
	return (1);
}

static char *ft_handle_double_quote(const char **input, t_parse_context *ctx) 
{
    const char *start;
    char *content;
    char *tmp;
    size_t i;

    content = NULL;
    i = 0;
    if (**input != '"')
        return (NULL);
    start = ++(*input);
    while ((*input)[i] && (*input)[i] != '"')
    {
        if ((*input)[i] == '$')
        {
            tmp = ft_extract_quotent(start, i);
            content = ft_concatent_content(content, tmp);
            if (!content || !tmp)
                return (NULL);
            
            if (!ft_handle_env_vars_quote(ctx))
                return (NULL);
            start = *input;
            i = 0;
        }
        else
            i++;
    }
    if ((*input)[i] != '"')
    {
        char    *test;
        test = ft_eof_double_quote(*input, ctx);
        // printf("input = %s\n", *input);
        if (!test)
            return (NULL);
        // tmp = ft_extract_quotent(start, i);
        content = ft_concatent_content(content, test);
        if (!content)
            return (NULL);
        (*input) += i + 1;
        return (content);
    }
    tmp = ft_extract_quotent(start, i);
    content = ft_concatent_content(content, tmp);
    if (!content)
        return (NULL);
    (*input) += i + 1;
    return (content);
}

char    *ft_eof_single_quote(const char *input, t_parse_context *ctx)
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
            ft_printf_fd(2, "bash: unexpected EOF while looking for matching `\''\n");
            free(line);
            free(new_str);
            return (NULL);
        }
        if (ft_strcmp(line, "\'") == 0)
        {
            free(line);
            break ;
        }
        new_str = ft_strjoin(new_str, "\n"); // leak here 
        new_str = ft_strjoin(new_str, line); // leak here 
    
/*        line = readline("> ");
        // ... error checking ...
        
        // Fix for newline addition
        char *tmp = new_str;
        new_str = ft_strjoin(tmp, "\n");
        free(tmp);
        
        // Fix for line addition
        tmp = new_str;
        new_str = ft_strjoin(tmp, line);
        free(tmp);
        free(line);
*/
    }
    new_str = ft_strjoin(new_str, "\n");
    history = ft_strjoin(new_str2, new_str);
    test = ft_split_built(history, '\'');
    add_history(history);
    // printf ("new_str = %s\n", test[1]);
    // free(history);
    return (test[1]);
}

static char *ft_handle_single_quote(const char **input, t_parse_context *ctx) 
{
    const char *start;
    char *content = NULL;
    size_t i;

    i = 0;
    if (**input != '\'')
        return (NULL);
    start = ++(*input);
    while ((*input)[i] && (*input)[i] != '\'')
        i++;
    if ((*input)[i] != '\'')
    {
        // ft_printf_fd(STDERR_FILENO, "minishell: syntax error: unclosed single quote\n");
        // return (NULL);
        if ((*input)[i] != '\'')
        {
            char    *test;
            test = ft_eof_single_quote(*input, ctx);
            // printf("input = %s\n", *input);
            if (!test)
                return (NULL);
            // tmp = ft_extract_quotent(start, i);
            content = ft_concatent_content(content, test);
            if (!content)
                return (NULL);
            (*input) += i + 1;
            return (content);
        }
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
    char *content;

    if (**ctx->input == '\'')
    {
        content = ft_handle_single_quote(ctx->input, ctx);
    } 
    else if (**ctx->input == '\"')
    {
        content = ft_handle_double_quote(ctx->input, ctx);
    }

    if (!content)
    {
        ft_printf_fd(STDERR_FILENO, "bash: syntax error: unexpected end of file\n");
        return (NULL);
    }
    return (content);
}