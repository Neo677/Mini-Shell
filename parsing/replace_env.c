/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:41:17 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/20 12:41:18 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_detec_var(const char **input)
{
	char	*var_name;

	var_name = ft_strndup(*input, 1);
	(*input)++;
	return (var_name);
}

int	ft_detec_digit(int is_digit_param, const char **input)
{
	if (ft_isdigit(**input))
		is_digit_param = 1;
	return (is_digit_param);
}
