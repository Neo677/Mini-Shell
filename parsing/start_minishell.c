/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:20:01 by thobenel          #+#    #+#             */
/*   Updated: 2025/01/13 13:20:03 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_abort(char *input)
{
	ft_printf("\n Bye bye ! 👋 \n");
	free(input);
	return ;
}

void	ft_abort_parse(char *input)
{
	printf("[ERROR] Invalid syntax\n");
	free(input);
	return ;
}

void	ft_abort_cmd(char *input, t_token *token)
{
	ft_printf("[ERROR] start error creating cmd\n");
	if (input)
		free(input);
	if (token)
		free(token);
	ft_clean_up(&token, &input);
	return ;
}
