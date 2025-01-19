/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:48:46 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/17 14:48:47 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_quotent(const char *start, size_t len)
{
	char	*tmp;

	tmp = ft_strndup(start, len);
	if (!tmp)
	{
		ft_printf("[DEBUG] Memory alloc failed in extract content\n");
		return (NULL);
	}
	return (tmp);
}

char	*ft_concatent_content(char *content, char *tmp)
{
	char	*new;

	if (content)
	{
		new = ft_strjoin(content, tmp);
		free(content);
		free(tmp);
		if (!new)
		{
			ft_printf("[ERROR] Memory allocation failed during concatenation\n");
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
