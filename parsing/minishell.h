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

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <time.h>
# include "../libft_v.2.0/libft.h"

// #define WIDTH 80    // Largeur du terminal (colonnes)
// #define HEIGHT 24   // Hauteur du terminal (lignes)
// #define DELAY 80000 // Délai entre chaque rafraîchissement (en microsecondes)

/*
	https://segfault42.github.io/posts/minishell/
                    🚨    🚨    🚨
	the easyes way to split the input is :
	1) take the input in a **char
	2) check if there is simple quote or double 
		(for ; & // not mandatory to work with it so just display an error)
	   use fonction for check the quote ou double 
		(because if there is no end to the quote like : 
		"... we need to printf everything like this is an str)
	4) if there is rediction etc ...
		we need to flag it and tell the exec there is this
	5)		enum list reference all the mandatory part of minishell dude :
		TOKEN_WORD,		 =====     simple word(ex : "ls", "echo", "file.txt")
		TOKEN_PIPE,		 =====     pipe '|'
		TOKEN_IN,		 =====     Redirections '<'
		TOKEN_OUT,		 =====     Redirections '>'
		TOKEN_APPEND,	 =====     Redirection en mode append '>>'
		TOKEN_HEREDOC,	 =====     Heredoc '<<'
		TOKEN_ENV_VAR,	 =====     Varibales d'envrionnement ('$VAR')
		TOKEN_QUOTE,	 =====     simple quote '\''
		TOKEN_DBL_QUOTE, =====     double quote '"'
		TOKEN_END,		 =====     fin de commande ou d'entrée 
*/

typedef enum e_token_arg
{
	TOKEN_WORD,	
	TOKEN_PIPE,
	TOKEN_IN,
	TOKEN_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_QUOTE,
	TOKEN_DBL_QUOTE,
	TOKEN_END,
	TOKEN_ERROR,
}		t_token_arg;

/*
		chain list for handle the token
		type ==  type du token in enum ⬆️
		valeur == valeur du token
		next == ptr for next token (chain list)
*/

typedef struct s_token
{
	t_token_arg		type;
	char			*value;
	struct s_token	*next;
}		t_token;

typedef struct s_redirections
{
	int						type;
	char					*file;
	struct s_redirections	*next;
}		t_redirections;

/*
		main structure for the command
	char **arg == tab de tab for the arguments of the command
	t_redirections *redirections == list of redirections associed to the command
	int 	p_pipe ==  1 si un pipe suit cette commande
	struct s_command *next == ptr for the next command (pipeline)
*/
typedef struct s_command
{
	char				**arg;
	t_redirections		*redirections;
	int					p_pipe;
	struct s_command	*next;
}		t_command;

//			main utils
void		ft_clean_up(t_token **token, char **input);
void		ft_handle_exit(char *input);

//			prompt
void		ft_intro(void);
void		ft_print_tokens(t_token *head);
void		matrix_effect(void);

//				error handler for different message
void		ft_error_pipe(const char *context);
int			ft_error_redirections(const char *context);
int			ft_error_quote(void);
int			ft_error_general(const char *context);
int			ft_error_env(const char *context);

//				env detection and syntax
int			ft_detect_env_var(const char *str);
char		*ft_extract_env_var(const char **input);
void		ft_handle_env_var(t_token **head, const char **input);

//				Token handler
char		*ft_handle_quote(const char **input, char quote);
void		ft_handle_operator(t_token **head, const char **input);
int			ft_is_redirection(t_token *token);
void		ft_handle_word(t_token **head, const char **input);
t_token		*ft_parse_token(const char *input);

//				Token creations
t_token_arg	ft_identify_token(char *str);
t_token		*ft_create_token(t_token_arg type, char *value);
void		ft_add_token(t_token **head, t_token *add);
void		ft_split_token(t_token **head, const char *input);

//				todo
t_command	*ft_create_command(t_command **lst);
void		ft_create_command_lst(t_token *token, t_command **lst);
int			ft_add_redirections(t_command *cmd, int type, const char *file);
int			ft_add_arguments(t_command *cmd, char *args);

//				Utils for token
int			ft_valid_redirections(t_token *token);
char		*ft_valid_quotes(char **current, char quote_type);
int			ft_validay_quotes(t_token *token);
int			ft_validay_pipes(t_token *token);
int			ft_valid_token(t_token *token);
char		*ft_get_next_token(const char **input);

//				Handle free and error 
void		ft_free_token(t_token *token);
void		error_exit(const char *error);
void		ft_free_redirection(t_redirections *redir);
void		ft_free_commande(t_command *command);

//				Utils
char		*ft_strndup(const char *src, size_t size);
int			ft_strcmp(char *s1, char *s2);

#endif