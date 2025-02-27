#include "minishell.h"

static char	*append_char_to_result(char *result, char c)
{
	char	letter[2];
	char	*tmp;

	letter[0] = c;
	letter[1] = '\0';
	tmp = result;
	result = ft_strjoin(result, letter);
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
		(*input)++;
	}
	if (**input == '"')
		(*input)++;
	else
		result = handle_missing_quote_part(result);
	return (result);
}

char	*ft_handle_double_quote(const char **input, t_parse_context *ctx)
{
	char	*quoted_content;
	char	*expanded_content;

	quoted_content = ft_collect_double_quote(input);
	if (!quoted_content)
		return (NULL);
	expanded_content = ft_expand_vars(quoted_content, ctx);
	free(quoted_content);
	return (expanded_content);
}
