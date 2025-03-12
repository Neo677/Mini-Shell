/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_d.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:32:23 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:32:24 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*handle_missing_quote_part(char *result)
{
	char	*tmp;
	char	*combined;

	tmp = ft_eof_double_quote();
	if (!tmp)
	{
		free(result);
		return (NULL);
	}
	combined = ft_strjoin(result, tmp);
	if (!combined)
	{
		free(result);
		free(tmp);
		return (NULL);
	}
	free(result);
	free(tmp);
	return (combined);
}

int	ft_count_quote(const char **input)
{
	char	*str;
	int		i;
	int		quote;

	i = 0;
	quote = 0;
	str = ft_strdup_v2(*input);
	while (str[i])
	{
		if (str[i] == '"')
			quote++;
		i++;
	}
	free(str);
	return (quote);
}

char	*ft_collect_double_quote(const char **input)
{
	char	*result;

	if (**input != '"')
		return (NULL);
	(*input)++;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (**input && **input != '"')
	{
		result = append_char_to_result(result, **input);
		if (!result)
			return (NULL);
		(*input)++;
	}
	if (**input == '"')
		(*input)++;
	else
		result = handle_missing_quote_part(result);
	return (result);
}

// char	*ft_collect_double_quote(const char **input)
// {
// 	char	*result;

// 	if (**input != '"')
// 		return (NULL);
// 	if (**input == '"' && **input + 1 == '"')
// 	{
// 		return (ft_strdup(""));
// 	}
// 	(*input)++;
// 	result = ft_strdup("");
// 	if (!result)
// 		return (NULL);
// 	while (**input)
// 	{
// 		result = append_char_to_result(result, **input);
// 		printf("{DEBUG} Result == %s\n", result);
// 		(*input)++;
// 	}
// 	if (**input == '"')
// 		(*input)++;
// 	else if (**input != '"')
// 		result = handle_missing_quote_part(result);
// 	return (result);
// }

char	*ft_handle_double_quote(const char **input, t_parse_context *ctx)
{
	char	*quoted_content;
	char	*expanded_content;
	int		i;

	quoted_content = ft_collect_double_quote(input);
	if (!quoted_content)
		return (NULL);
	i = 0;
	while (quoted_content[i])
	{
		if (quoted_content[i] == '$')
		{
			expanded_content = ft_expand_vars(quoted_content, ctx);
			free(quoted_content);
			return (expanded_content);
		}
		i++;
	}
	return (quoted_content);
}
