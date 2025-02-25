#include "minishell.h"

/*
	ft_eof_double_quote :
	Lit des lignes supplémentaires jusqu'à trouver une ligne
		contenant uniquement une double quote.
	Renvoie le contenu accumulé (les retours à la ligne sont conservés).
 */

#include "minishell.h"

static char	*append_line(char *acc, char *line)
{
	char	*tmp;
	char	*new_acc;

	tmp = acc;
	new_acc = ft_strjoin(tmp, "\n");
	free(tmp);
	tmp = new_acc;
	new_acc = ft_strjoin(tmp, line);
	free(tmp);
	return (new_acc);
}

char	*ft_eof_double_quote(void)
{
	char	*line;
	char	*new_str;

	new_str = ft_strdup("");
	if (!new_str)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (free(new_str), NULL);
		if (ft_strcmp(line, "\"") == 0)
		{
			free(line);
			break ;
		}
		new_str = append_line(new_str, line);
		free(line);
	}
	return (new_str);
}

char	*ft_read_until_S_quote(void)
{
	char	*line;
	char	*acc;
	char	*tmp;

	acc = ft_strdup("");
	if (!acc)
		return (NULL);
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (free(line), NULL);
		if (ft_strcmp(line, "\'") == 0)
		{
			free(line);
			break ;
		}
		tmp = acc;
		acc = ft_space_swap(acc, tmp, line);
	}
	tmp = acc;
	acc = ft_strjoin(acc, "\n");
	return (free(tmp), acc);
}

char	*ft_eof_single_quote(t_parse_context *ctx)
{
	char	*extra;
	char	*history;
	char	**parts;
	char	*new_str2;

	new_str2 = ft_strdup_v2(ctx->input_exec);
	if (!new_str2)
		return (NULL);
	extra = ft_read_until_S_quote();
	if (!extra)
	{
		ft_printf_fd(2,
			"bash: unexpected EOF while looking for matching `\''\n");
		return (free(new_str2), NULL);
	}
	history = ft_strjoin(new_str2, extra);
	free(new_str2);
	parts = ft_split_built(history, '\'');
	add_history(history);
	free(history);
	return (parts[1]);
}
