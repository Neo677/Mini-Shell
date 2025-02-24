#include "minishell.h"

static size_t	ft_get_var_len(const char *input, size_t i)
{
	size_t	j;

	if (input[i + 1] == '$' || input[i + 1] == '?')
		return (2);
	j = i + 1;
	while (input[j] && (ft_isalnum(input[j]) || input[j] == '_'))
		j++;
	return (j - i);
}

static char	*get_env_var_value(char *var, t_parse_context *ctx)
{
	char	*env_value;
	char	*var_value;
	char	*old;

	env_value = print_node_by_key(ctx->env_cpy, var + 1);
	if (env_value)
	{
		var_value = ft_strdup(env_value);
		if (!var_value)
			return (NULL);
		if (check_variable_backslash_n_parse(var_value) == 1)
		{
			old = var_value;
			var_value = replace_with_space_parse(var_value);
			free(old);
		}
	}
	else
		var_value = NULL;
	return (var_value);
}

static char	*get_var_value(const char *input, size_t var_len,
		t_parse_context *ctx)
{
	char	*var_name;
	char	*var_value;

	var_name = ft_strndup(input, var_len);
	if (!var_name)
		return (NULL);
	if (ft_strcmp(var_name, "$$") == 0)
	{
		free(var_name);
		var_value = ft_get_pid_str();
	}
	else if (ft_strcmp(var_name, "$?") == 0)
	{
		free(var_name);
		var_value = ft_itoa(ctx->exit_status);
	}
	else
	{
		var_value = get_env_var_value(var_name, ctx);
		free(var_name);
	}
	return (var_value);
}

static char	*process_variable(const char *input, size_t *i, char *resl,
		t_parse_context *ctx)
{
	size_t	var_len;
	char	*var_value;
	char	*tmp;

	var_len = ft_get_var_len(input, *i);
	var_value = get_var_value(input + *i, var_len, ctx);
	if (var_value)
	{
		tmp = resl;
		resl = ft_strjoin(resl, var_value);
		free(tmp);
		free(var_value);
	}
	else
	{
		tmp = resl;
		resl = ft_strjoin(resl, "");
		free(tmp);
	}
	*i += var_len;
	return (resl);
}

static char	*append_char(char *res, char c)
{
	char	letter[2];

	letter[0] = c;
	letter[1] = '\0';
	return (ft_strjoin(res, letter));
}

char	*ft_expand_vars(const char *input, t_parse_context *ctx)
{
	size_t i;
	char *resl;
	char *tmp;

	i = 0;
	resl = ft_strdup("");
	if (!resl)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
			resl = process_variable(input, &i, resl, ctx);
		else
		{
			tmp = resl;
			resl = append_char(resl, input[i]);
			free(tmp);
			i++;
		}
	}
	return (resl);
}