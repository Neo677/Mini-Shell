/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 05:01:29 by thobenel          #+#    #+#             */
/*   Updated: 2025/03/19 22:01:15 by dpascal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../exec/include/exec.h"
# include "../libft_2.0/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

extern int					g_signal;
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
		TOKEN_WORD,			=====     simple word(ex : "ls", "echo", "file.txt")
		TOKEN_PIPE,			=====     pipe '|'
		TOKEN_IN,			=====     Redirections '<'
		TOKEN_OUT,			=====     Redirections '>'
		TOKEN_APPEND,		=====     Redirection en mode append '>>'
		TOKEN_HEREDOC,		=====     Heredoc '<<'
		TOKEN_ENV_VAR,		=====     Varibales d'envrionnement ('$VAR')
		TOKEN_QUOTE,		=====     simple quote '\''
		TOKEN_DBL_QUOTE, =====     double quote '"'
		TOKEN_END,			=====     fin de commande ou d'entrée

		chain list for handle the token
		type ==  type du token in enum ⬆️
		valeur == valeur du token
		next == ptr for next token (chain list)

		main structure for the command
	char **arg == tab de tab for the arguments of the command
	t_redirections *redirections == list of redirections associed to the command
	int 	p_pipe ==  1 si un pipe suit cette commande
	struct s_command *next == ptr for the next command (pipeline)
*/

typedef enum e_token_type
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
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*next;
}							t_token;

typedef struct s_redirections
{
	int						type;
	int						is_literal;
	char					*file;
	struct s_redirections	*next;
}							t_redirections;

typedef struct s_command
{
	char					**arg;
	t_redirections			*redirections;
	int						p_pipe;
	struct s_command		*next;
}							t_command;

typedef struct s_quote
{
	const char				*start;
	size_t					i;
}							t_quote;

typedef struct s_pipex		t_pipex;
typedef struct s_built_in	t_buit_in;
typedef struct s_env		t_env;

typedef struct s_parse_context
{
	const char				**input;
	const char				*input_exec;
	t_token					**head;
	t_token					*last_token;
	t_command				**cmd_lst;
	t_command				**current;
	t_env					**env_cpy;
	int						exit_status;
	int						*last_exit_status;
	int						flag_heredoc;
}							t_parse_context;

typedef struct s_shell_context
{
	t_buit_in				*exec;
	t_pipex					*pipex;
	t_command				**cmd_lst;
	int						*lst;
}							t_shell_context;

int							ft_add_arguments(t_command *cmd, const char *arg);

int							ft_add_redirections_struct(t_command *cmd, int type,
								const char *file, t_parse_context *ctx);

int							run_shell(t_buit_in *exec);
int							ft_strcmp_shell(char *s1, char *s2);

void						ft_free_command(t_command *cmd);
void						ft_free_command_list(t_command **lst);
t_command					*ft_init_command(t_command **lst);
int							ft_create_command_lst(t_token *token,
								t_command **lst, t_parse_context *ctx);

void						ft_create_cmd_pipe(t_command **current);
int							ft_create_cmd_word(t_command **current,
								t_token *token, t_command **lst);
int							ft_create_cmd_redirect(t_command **current,
								t_token *token, t_command **lst,
								t_parse_context *ctx);
int							ft_create_cmd_env(t_command **current,
								t_token *token, t_command **lst);

char						*ft_get_pid_str(void);
char						*ft_detec_var(const char **input);
int							ft_detec_digit(int is_digit_param,
								const char **input);
char						*ft_extract_env_var(const char **input);
char						*ft_handle_special_case(const char **input);
char						*ft_extract_digit_var(const char **input);
char						*ft_extract_alpha_var(const char **input);

void						error_exit(const char *error);
void						ft_free_token(t_token *head);
void						ft_free_redirection(t_redirections *redir);
void						ft_free_commande_lst(t_command *command);
void						ft_main_free(t_command *cmd, t_redirections *redir,
								t_token *head);

void						setup_shell_signals(void);

void						setup_exec_signals(void);
void						setup_child_signals(void);
void						setup_heredoc_signals(void);
void						restore_shell_signals(void);

void						ft_setup_env(t_buit_in *exec, char **env);
void						util_proc(t_buit_in *exec, t_token *token,
								t_pipex *pipex);
void						ft_end_process(t_token *token, t_buit_in *exec,
								t_pipex *pipex);
void						ft_init_proc(t_parse_context ctx, int *lst,
								t_buit_in *exec);
int							process_line(t_buit_in *exec, t_pipex *pipex,
								t_command **cmd_lst, int *lst);

int							is_valid_var_char(char c);
char						*handle_dollar(const char *str, size_t *i,
								t_parse_context *ctx, char *result);
char						*ft_expand_variables(const char *str,
								t_parse_context *ctx);

int							ft_free_process_line(t_buit_in *exec,
								t_pipex *pipex, t_command **cmd_lst,
								t_token *token);
int							read_input(t_buit_in *exec);

int							is_minishell_call(t_shell_context *ctx);

int							handle_minishell_cmd(t_shell_context *ctx,
								t_token *token);
int							process_cmd(t_buit_in *exec, t_shell_context *ctx,
								t_token *token);

void						ft_free_split(t_token **head, t_command **cmd_lst,
								const char *error_msg, const char *token);
;
void						ft_err_split(t_command *cmd_lst, t_token *head);
void						ft_err_split_ope(t_command *cmd_lst, t_token *head);
void						ft_err_bad_redirec(t_command *cmd_lst,
								t_token *head);

void						ft_error_pipe(const char *context);
void						ft_error_redirections(const char *context);
int							ft_error_quote(void);
int							ft_error_general(const char *context);
int							ft_error_env(const char *context);

char						*ft_extract_quotent(const char *start, size_t len);
char						*ft_concatent_content(char *content, char *tmp);
int							ft_update_ptr_input(const char **input, size_t *i,
								const char **start);
char						*ft_strjoin_free(char *s1, char *s2);
char						*ft_space_swap(char *acc, char *tmp, char *line);

char						*ft_eof_double_quote(void);
char						*ft_eof_single_quote(void);

int							ft_handle_env_vars_quote(t_parse_context *ctx);

size_t						ft_get_var_len(const char *input, size_t i);
char						*get_env_var_value(char *var, t_parse_context *ctx);
char						*get_var_value(const char *input, size_t var_len,
								t_parse_context *ctx);
char						*process_variable(const char *input, size_t *i,
								char *resl, t_parse_context *ctx);
char						*append_char(char *res, char c);

char						*ft_expand_vars(const char *input,
								t_parse_context *ctx);

char						*ft_handle_double_quote(const char **input,
								t_parse_context *ctx);
char						*ft_handle_single_quote(const char **input,
								t_parse_context *ctx);
char						*ft_handle_quote(t_parse_context *ctx);

t_token						*ft_parse_token(const char *input, t_env **env_cpy,
								t_command **cmd_lst, int *last_exit_status);

void						ft_print_tab(char **tab);
void						ft_print_redirections(t_redirections *head);
void						ft_print_command_lst(t_command *head);
void						ft_print_tokens(t_token *head);

int							ft_handle_quotes(t_parse_context *ctx);
int							handle_quote_with_next(t_parse_context *ctx,
								char *quote);
int							merge_with_next(t_parse_context *ctx, char *quote);
char						*build_quote_content(t_parse_context *ctx);

char						*extract_str(char *var_name);
int							ft_strchr_comp_dol(char *var_name);
int							ft_strchr_comp_quest(char *var_name);

int							ft_handle_doles(t_parse_context *ctx,
								char *var_name);
int							ft_handle_dolquestes(t_parse_context *ctx,
								char *var_name);
int							ft_handle_doldoles(t_parse_context *ctx,
								char *var_name);

char						*replace_dol(char *var_value, char *var_name);
char						*replace_quest(char *var_value, char *var_name);
int							count_replace_quest(char *var_value,
								char *var_name);
int							count_replace_dol(char *var_value, char *var_name);

int							ft_handle_operators(t_parse_context *ctx);
int							ft_handle_env_vars(t_parse_context *ctx,
								int *last_exit_status);
int							ft_handle_words(t_parse_context *ctx);

int							ft_handle_alones(t_parse_context *ctx,
								char *var_name);
int							count_replace_quest(char *var_value,
								char *var_name);
int							count_replace_dol(char *var_value, char *var_name);

int							ft_strcmp_dollar(char *varname);
char						*replace_dol(char *var_value, char *var_name);
int							fill_result_dol(char *result, char *var_value,
								char *var_name);
int							fill_result_quest(char *result, char *var_value,
								char *var_name);

char						*replace_quest(char *var_value, char *var_name);

int							process_tokens(t_parse_context *ctx,
								int *last_exit_status);
int							error_cleanup(t_parse_context *ctx,
								int *last_exit_status);

void						ft_let_go_split(t_parse_context ctx,
								int *last_exit_status);
void						init_cmd_ctx(t_parse_context *ctx,
								t_command **cmd_lst, t_command **current);
int							finalize_ctx(t_parse_context *ctx,
								int *last_exit_status);

int							ft_split_token(t_token **head, const char *input,
								t_env **env_cpy, int *last_exit_status);

void						ft_abort(char *input);
void						ft_abort_parse(char *input);
void						ft_abort_cmd(char *input, t_token *token);

int							ft_check_syntax(const char *input,
								t_parse_context *ctx);
int							ft_set_syntax_ope(const char *input, int i,
								t_parse_context *ctx);
void						ft_set_syntax_redir_2(const char *input, int j);
void						ft_set_syntax_redir_1(int len, char op);
int							ft_set_syntax_pipe(const char *input, int i,
								t_parse_context *ctx);
void						ft_print_err_global(int i);
void						ft_pass_this_bro(t_parse_context *ctx);

int							ft_is_redirection(t_token *token);
int							ft_handle_operator(t_token **head,
								const char **input, t_parse_context *ctx);

t_token_type				ft_identify_token(char *str);
t_token						*ft_create_token(t_token_type type, char *value);
void						ft_add_token(t_token **head, t_token *new_token);
char						*ft_get_next_token(const char **input);
t_token						*ft_last_token(t_token *head);

void						ft_clean_up(t_token **token, char **input);
int							ft_handle_exit(char *input);
void						ft_intro(void);

size_t						ft_strnlen(const char *s, size_t max);
char						*ft_strncpy(char *dst, const char *src, size_t len);
char						*ft_strndup(const char *src, size_t size);
int							ft_strcmp_parsing(char *s1, char *s2);
char						*replace_with_space_parse(char *str);
int							check_variable_backslash_n_parse(char *value);
int							ft_isspace(char c);

int							ft_valid_redirections(const t_token *token);
char						*ft_valid_quotes(char **current, char quote_type);
int							ft_validay_quotes(t_token *token);
int							ft_validate_pipes(t_token *token,
								t_parse_context *ctx);
int							ft_valid_env_var(t_token *token);
int							ft_valid_token(t_token *token,
								t_parse_context *ctx);

void						ft_pass_this_bro(t_parse_context *ctx);
char						*ft_strdup_v2_quote(const char *src);
int							merge_quote_with_last(t_parse_context *ctx,
								char *quote_content);
int							add_quote_as_new_token(t_parse_context *ctx,
								char *quote_content);

int							ft_handle_alones(t_parse_context *ctx,
								char *var_name);

#endif
