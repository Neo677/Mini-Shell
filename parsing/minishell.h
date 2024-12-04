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
# include <readline/history.h>
# include <readline/readline.h>

# include "../../libft_v.2.0/libft.h"

//  https://segfault42.github.io/posts/minishell/


/*
	the easyes way to split the input is :
	1) take the input in a **char
	2) check if there is simple quote or double 
		(for ; & // not mandatory to work with it so just display an error)
	   use fonction for check the quote ou double 
		(because if there is no end to the quote like : "... we need to printf everything like this is an str)
	4) if there is rediction etc ...
		we need to flag it and tell the exec there is this
	5)
*/
typedef enum e_token_arg
{
	TOKEN_WORD,		//simple word(ex : "ls", "echo", "file.txt")
	TOKEN_PIPE,		// pipe '|'
	TOKEN_IN,		// Redirections '<'
	TOKEN_OUT,		// Redirections '>'
	TOKEN_APPEND,	// Redirection en mode append '>>'
	TOKEN_HEREDOC,	// Heredoc '<<'
	TOKEN_ENV_VAR,	// Varibales d'envrionnement ('$VAR')
	TOKEN_QUOTE,	// simple quote '\''
	TOKEN_DBL_QUOTE,// double quote '"'
	TOKEN_END,		// fin de commande ou d'entrée 
}			t_token_arg;

// chain list for handle the token
typedef struct s_token
{
	t_token_arg type; //  type du token in enum ⬆️
	char *value;	 // valeur du token
	struct s_token *next; // ptr for next token (chain list)
}				t_token;

// main structure for the command
typedef struct s_command
{
	char **arg;			// tab de tab for the arguments of the command
	t_token *redirections; // list of redirections associed to the command
	struct s_command *next; // ptr for the next command (pipeline)
}				t_command;


#endif
