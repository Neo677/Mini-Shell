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

# include "../libft_v.2.0/libft.h"

//  https://segfault42.github.io/posts/minishell/

/*
                    🚨    🚨    🚨
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

typedef struct s_redirections
{
	int type;
	char *file;
	struct s_redirections *next;
}				t_redirections;

// main structure for the command
typedef struct s_command
{
	char **arg;			// tab de tab for the arguments of the command
	t_token *redirections; // list of redirections associed to the command
	int 				p_pipe; // 1 si un pipe suit cette commande
	struct s_command *next; // ptr for the next command (pipeline)
}				t_command;


//				printf fonction
void    ft_print_token(t_token *token);
char *ft_handle_quotes(char **current, char quote_type);

//				Token segmentation
char *ft_handle_quote(char **input, char quote);
void    ft_handle_operator(t_token **head, const char **input);
void ft_handle_word(t_token **head, const char **input);


//				Token creations
t_token_arg ft_identify_token(const char *str);
t_token *ft_create_token(t_token_arg type, char *value);
void    ft_add_token(t_token **head, t_token *add);
void    ft_split_token(t_token **head, const char *input);

t_command *ft_create_command(void);
int ft_add_redirections(t_command *cmd, int type, const char *file);
void     ft_add_arguments(t_command *cmd, char *args);

//				Utils for token
int     ft_is_redirections(t_token *token);
int ft_valid_pipes(t_token *token, t_token *prev);
int ft_valid_token(t_token *token);
char *ft_get_next_token(const char **input);

//				Handle free and error 
void	ft_free_token(t_token *token);
void	error_exit(const char *error);

//				Utils
char *ft_strndup(const char *src, size_t size);
int ft_strcmp(char *s1, char *s2);



#endif
