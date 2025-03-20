/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:47:45 by dpascal           #+#    #+#             */
/*   Updated: 2025/03/20 09:39:47 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

void	init_var_builtin(t_buit_in *exec)
{
	exec->env_cpy = NULL;
	exec->export_cpy = NULL;
	exec->tab = NULL;
	exec->input = 0;
	exec->cd = 0;
	exec->exit_bh = 0;
	exec->exit_code_bh = 0;
	exec->cur_ex = NULL;
	exec->new_node_export = NULL;
	exec->env_cpy = NULL;
	exec->cpy_env_cpy_export = NULL;
	exec->tab_export = NULL;
	exec->value_export = NULL;
	exec->status = 0;
	exec->i = 0;
	exec->hd = 0;
}
