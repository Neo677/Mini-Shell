#include "minishell.h"

char	*ft_use_double(const char *start, t_parse_context *ctx)
{
	char	*first_line;
	char	*rest;
	char	*combined;
	char	*tmp;
	size_t	len_first;

	len_first = ft_strlen_v2(start);
	first_line = ft_extract_quotent(start, len_first);
	rest = ft_eof_double_quote();
	if (!rest)
	{
		ft_printf_fd(2,
			"bash: unexpected EOF while looking for matching `\"'\n");
		return (NULL);
	}
	combined = ft_strjoin(first_line, rest);
	free(first_line);
	free(rest);
	tmp = ft_expand_vars(combined, ctx);
	free(combined);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*handle_dollar_in_quote(const char **input, t_parse_context *ctx,
		t_quote *state, char *content)
{
	char	*tmp;

	tmp = ft_extract_quotent(state->start, state->i);
	content = ft_concatent_content(content, tmp);
	if (!content)
		return (NULL);
	ft_handle_env_vars_quote(ctx);
	state->start = *input;
	state->i = 0;
	return (content);
}

char	*ft_missing_quote(const char **input, t_quote state,
		t_parse_context *ctx)
{
	char	*tmp;

	tmp = ft_use_double(state.start, ctx);
	if (!tmp)
		return (NULL);
	*input += state.i + 1;
	return (tmp);
}

char	*ft_closing_quote(const char **input, t_quote state, char *content)
{
	char	*tmp;

	tmp = ft_extract_quotent(state.start, state.i);
	content = ft_concatent_content(content, tmp);
	if (!content)
		return (NULL);
	*input += state.i + 1;
	return (content);
}

char	*ft_handle_double_quote(const char **input, t_parse_context *ctx)
{
	t_quote	state;
	char	*content;

	content = NULL;
	if (**input != '"')
		return (NULL);
	(*input)++;
	state.start = *input;
	state.i = 0;
	while ((*input)[state.i] && (*input)[state.i] != '"')
	{
		if ((*input)[state.i] == '$')
		{
			content = handle_dollar_in_quote(input, ctx, &state, content);
			if (!content)
				return (NULL);
		}
		else
			state.i++;
	}
	if ((*input)[state.i] != '"')
		return (ft_missing_quote(input, state, ctx));
	return (ft_closing_quote(input, state, content));
}
