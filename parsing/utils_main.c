/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:25:41 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/12 17:25:42 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_clean_up(t_token **token, char **input)
{
    if (token && *token)
        ft_free_token(*token);
    if (input && *input)
        free(*input);
}

void    ft_handle_exit(char *input)
{
    if (ft_strcmp(input, "exit") == 0)
    {
        printf("Bye Bye !! 👋\n");
        exit(0);
    }
}
