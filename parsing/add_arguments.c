/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_arguments.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:24:18 by thobenel          #+#    #+#             */
/*   Updated: 2025/02/12 05:09:38 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
					🚨    🚨    🚨
	for here this is the same goal as add_redirections.c
	but we only need to add a command
	here we add 2️⃣ arguments to the command :
		the command and the arguments im self (like : ls or cat etc ...)
	so we jsut need to put it in a chain list who name t_command
	for doing that we can :
	1) initialise the cmd->arg if he as no space in memory
	2) the first while is use to calcul the size of the arguments
	3) after we got the size we can add it as a node
*/

static void	ft_add_arg_utls(t_command *cmd, char **new_arg)
{
	int	i;

	i = 0;
	while (cmd->arg[i])
	{
		new_arg[i] = cmd->arg[i];
		i++;
	}
}

int	ft_add_arguments(t_command *cmd, const char *arg)
{
	int		i;
	char	**new_arg;

	if (!cmd || !arg)
		return (0);
	i = 0;
	if (cmd->arg)
		while (cmd->arg[i])
			i++;
	new_arg = malloc(sizeof(char *) * (i + 2));
	if (!new_arg)
		return (0);
	if (cmd->arg)
		ft_add_arg_utls(cmd, new_arg);
	new_arg[i] = ft_strdup_v2(arg);
	if (!new_arg[i])
	{
		free(new_arg);
		return (0);
	}
	new_arg[i + 1] = NULL;
	free(cmd->arg);
	cmd->arg = new_arg;
	return (1);
}
