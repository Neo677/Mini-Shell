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

void    ft_replace_token_env_var(t_token **head, t_env *env)
{
    t_token *current;
    t_env *current_env;
    char *value;

    current = *head;
    while (current)
    {
        if (current->type == TOKEN_ENV_VAR)
        {
            current_env = env;
            while (current_env)
            {
                if (!ft_strcmp(current_env->key, current->value))
                {
                    value = ft_strdup(current_env->value);
                    free(current->value);
                    current->value = value;
                    break;
                }
                current_env = current_env->next;
            }
        }
        current = current->next;
    }
}