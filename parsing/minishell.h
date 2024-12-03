/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thobenel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:59:14 by thobenel          #+#    #+#             */
/*   Updated: 2024/12/02 12:59:15 by thobenel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>

# include "libft_v.2.0/libft.h"

//https://segfault42.github.io/posts/minishell/

typedef struct ms_arg_s
{

	struct ms_arg_s *next;
}				ms_arg_t;

typedef struct ms_node_arg_s
{
	
	struct ms_node_arg_s *next;
}				ms_node_arg_t;


#endif // ! MINISHELL_H