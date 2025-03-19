/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 09:25:51 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/03 09:25:52 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

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

char	*ft_space_swap(char *acc, char *tmp, char *line)
{
	acc = ft_strjoin(acc, "\n");
	free(tmp);
	tmp = acc;
	acc = ft_strjoin(acc, line);
	free(tmp);
	free(line);
	return (acc);
}

char	*ft_extract_quotent(const char *start, size_t len)
{
	char	*tmp;

	tmp = ft_strndup(start, len);
	if (!tmp)
		ft_printf_fd(2,
			"minishell: error memory allocation failed\n");
	return (tmp);
}

char	*ft_concatent_content(char *content, char *tmp)
{
	char	*new;

	if (content)
	{
		new = ft_strjoin_v2(content, tmp);
		free(tmp);
		if (!new)
			ft_printf_fd(2,
				"minishell: error allocation failed during concatenation\n");
		return (new);
	}
	return (tmp);
}
