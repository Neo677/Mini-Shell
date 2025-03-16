/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:48:03 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/14 18:15:44 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	ft_unset(t_buit_in *exec, t_env **env_cpy, char *key)
{
	if (!key)
	{
		exec->status = 0;
		return ;
	}
	delete_node_by_key(env_cpy, key);
}
