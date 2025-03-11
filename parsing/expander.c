/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 08:27:29 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 08:27:32 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*process_variable(const char *input, size_t *i, char *resl,
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
		*i += var_len;
		return (resl);
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

char	*append_char(char *res, char c)
{
	char	letter[2];

	letter[0] = c;
	letter[1] = '\0';
	return (ft_strjoin(res, letter));
}

char	*ft_expand_vars(const char *input, t_parse_context *ctx)
{
	size_t	i;
	char	*resl;
	char	*tmp;

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
