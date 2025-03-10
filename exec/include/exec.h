#ifndef EXEC_H
# define EXEC_H

# include "../../parsing/minishell.h"
# include "../libft/printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

# define CD_ERR "cd: error retrieving current directory: getcwd: cannot "
# define CD_ERR2 "access parent directories: No such file or directory\n"
# define EXIT_ERR "bash: exit: %s: numeric argument required\n"
# define CMD_EXEC "bash: .: filename argument required\n.: "
# define CMD_EXEC2 "usage: . filename [arguments]\n"
# define HD_1 "bash: warning: here-document at line %d "
# define HD_2 "delimited by end-of-file (wanted `%s')\n"

typedef struct s_env
{
	char						*key;
	char						*value;
	int							val;
	struct s_env				*next;
}								t_env;

typedef struct s_built_in
{
	t_env						*env_cpy;
	t_env						*export_cpy;
	char						**env_dup;
	char						**tab;
	char						*input;
	int							cd;
	int							exit_bh;
	int							exit_code_bh;
	t_env						*cur_ex;
	t_env						*new_node_export;
	t_env						**env_cpy_export;
	t_env						*cpy_env_cpy_export;
	char						**tab_export;
	char						*value_export;
	int							status;
}								t_buit_in;

typedef struct s_pipex
{
	int							infile;
	int							outfile;
	char						**paths;
	char						*path;
	char						*paths_cmd;
	char						*path_cmd;
	char						**filename_hd;
	int							line_hd;
	int							pipe_fd[2];
	int							prev_pipe;
	int							cmd_count;
	int							status;
	pid_t						pid;
	int							i;
}								t_pipex;

typedef struct s_token			t_token;
typedef struct s_redirections	t_redirections;
typedef struct s_command		t_command;
typedef struct s_parse_context	t_parse_context;

/* BUILT_IN  */

/*  CD  */
char							*modify_pwd_with_arg(char *path, char *arg);
int								modify_path(char *arg, t_env **env);
int								arg_cd(t_buit_in *exec, char *arg, t_env **env);
int								ft_cd(t_buit_in *exec, t_env **env, char **arg);

/*  CMD_NODE  */
t_env							*create_node(char *key, char *value);
int								modify_node_value(t_env **env_cpy, char *key,
									char *new_value);
int								delete_node_by_key(t_env **env_cpy, char *key);

/*  CPY_ENV  */
int								check_value(char *str);
char							*parse_value(char *input);
char							**init_create_key_value(char *env);
t_env							*create_key_value(char *env);
void							copy_env(char **env, t_env **env_cpy);

/*  ECHO  */
int								check_option_echo(char *str);
void							print_echo(t_command *cmd, int i,
									int line_break);
void							ft_echo(t_command *cmd);

/*  ENV  */
void							ft_env(t_env **env_cpy);

/*  EXIT  */
int								ft_numeric(char *arg);
int								atol_sign(char *str, int i, int *sign);
long long						ft_atol(char *str, int *error);
int								error_ft_exit(t_buit_in *exec, char **tab);
int								ft_exit(t_buit_in *exec, char **tab);

/*  EXPORT  */
int								c_var_value(t_buit_in *exec, t_env **env_cpy,
									char **key_value, int i);
int								check_n_c_key(t_buit_in *exec, t_env **env_cpy,
									char **key_value, int i);
int								value_exist(t_buit_in *exec, t_env **env_cpy,
									char **key_value, int i);
int								ft_export(t_buit_in *exec, t_env **env_cpy,
									char **key_value);

/*  EXPORT_2  */
void							init_export(t_buit_in *exec, t_env **env_cpy);
void							printf_export(t_buit_in *exec);
int								split_n_check(t_buit_in *exec, char **key_value,
									int i);
int								create_new_node(t_buit_in *exec,
									t_env **env_cpy, char **key_value, int i);
int								c_var_key(t_buit_in *exec, t_env **env_cpy,
									char **key_value, int i);

/*  EXPORT_3  */
int								ft_swap(t_env *a, t_env *b);
t_env							*sort_list(t_env **env_cpy);
t_env							**export_cpy(t_env **env_cpy,
									t_env **cpy_env_cpy);

/*  FREE_BH  */
void							free_char(char *str);
void							free_list(t_env **lst);
void							free_env_list(t_env *head);
void							free_node(t_env *node);
void							free_all(t_buit_in *exec);

/*  INIT  */
void							init_var_builtin(t_buit_in *exec);

/*  PWD  */
int								pwd_with_cd(t_env **env, int cd);
void							ft_pwd(t_env **env, int cd);

/*  SIGNAL  */
void							signal_handler(int sig);
void							signal_handler2(int sig);

/*  SPLIT_VAR  */
int								ft_strlen_c(char *str, int i, char c);
char							**init_split_in_two(char *str, char c);
char							**split_in_two(char *str, char c);

/*  SPLIT  */
int								ft_count(char *s, char c);
int								ft_len(char *str, char c, int i);
char							**ft_split_init(char *str, char c, char **tab);
char							**ft_split_built(char *str, char c);

/*  UNSET  */
void							ft_unset(t_buit_in *exec, t_env **env_cpy,
									char *key);

/*  UTILS_BUILT_IN  */
int								ft_strlen(char *s);
char							*ft_strdup(char *src);
int								ft_strcmp(char *s1, char *s2);
char							*ft_join(char *join, char *s1, char *s2);
char							*ft_strjoin(char *s1, char *s2);

/*  UTILS_CMD_NODE  */
int								search_node_and_value(t_env **env, char *key,
									char *value);
int								search_by_key(t_env **env, char *key);
char							*print_node_by_key(t_env **env, char *key);

/*  UTILS_EXPORT  */
int								check_key_export(char *str);
char							*init_remove_backslash(char *str);
char							*remove_backslash(char *str);
char							*replace_b_n(char *value);
int								check_b_n(char *value);

/*  UTILS  */

/*  CORE  */

/*  BUILTIN  */
int								check_built_in(char *str);
int								execute_built_in(t_buit_in *exec,
									t_command *cmd);

/*  CHECK_FILE  */
int								check_file_in(t_buit_in *exec, t_token *token);
int								check_file_out(t_buit_in *exec, t_token *token);
int								check_file(t_buit_in *exec, t_token *token);

/*  CHECK_FILE  */
int								check_file_in2(t_buit_in *exec,
									t_redirections *current);
int								check_file_out2(t_buit_in *exec,
									t_redirections *current);
int								check_file2(t_buit_in *exec, t_command *cmd);

/*  CMD  */
char							*error_execute_cmd(t_buit_in *exec,
									t_pipex *pipex, char *cmd);
char							*find_cmd(t_buit_in *exec, t_pipex *pipex,
									char *cmd, char **paths);
char							*find_path(t_buit_in *exec, t_pipex *pipex,
									char *cmd, char **envp);
void							execute_cmd(t_buit_in *exec, t_pipex *pipex,
									char **arg, char **envp);

/*  FREE_EXEC  */
void							free_tab(char **tab);
void							free_all_core(t_pipex *pipex);
void							close_file(t_pipex *pipex);
void							free_error(t_pipex *pipex, int key_error);

/*  HERE_DOC  */
char							*heredoc_name(int i);
void							init_hd(t_token *token, t_pipex *pipex);
void							while_hd(t_pipex *pipex, t_token *current,
									int heredoc_fd);
void							set_while_hd(t_pipex *pipex, t_token *current);
int								check_heredoc(t_token *token, t_pipex *pipex);

/*  INIT_VAR  */
void							init_var(t_pipex *pipex);
void							init_process(t_pipex *pipex, t_command *cmd);

/*  PROCESS  */
int								one_command(t_pipex *pipex, t_buit_in *exec,
									char **env, t_command *current);
int								child_process(t_pipex *pipex, t_buit_in *exec,
									char **env, t_command *current);
int								while_commands(t_pipex *pipex, t_buit_in *exec,
									char **env, t_command **current);
int								more_commands(t_pipex *pipex,
									t_command *current, t_buit_in *exec,
									char **env);
void							process(t_pipex *pipex, t_command *cmd,
									t_buit_in *exec, char **env);

/*  PROCESS  */
int								no_built_in(t_pipex *pipex, t_buit_in *exec,
									char **env, t_command *current);

/*  REDIR  */
void							check_redir_2(t_buit_in *exec, t_pipex *pipex,
									t_redirections *redirection);
void							check_dir_5(t_buit_in *exec, t_pipex *pipex,
									t_redirections *redirection, int *i);
int								redir_input(t_buit_in *exec, t_command *cmd,
									t_pipex *pipex);
void							check_n_change_out(t_buit_in *exec,
									t_pipex *pipex,
									t_redirections *redirection);
int								redir_output(t_buit_in *exec, t_command *cmd,
									t_pipex *pipex);

/*  SPLIT  */
int								ft_count_pipex(char *s, char c);
int								ft_len_pipex(char *str, char c, int i);
char							**ft_split_init_pipex(t_pipex *pipex, char *str,
									char c, char **tab);
char							**ft_split_pipex(t_pipex *pipex, char *str,
									char c);

/*  UTILS_ERROR  */
char							*ft_join_pipex(char *join, char *s1, char *s2);
char							*ft_strjoin_pipex(char *s1, char *s2);
void							write_error(char *cmd);

/*  UTILS  */
int								ft_strchr_exec(char *str, char c);
int								ft_strlen_exec(int nb);
int								ft_strlen_pipex(char *s);
char							*ft_itoa_exec(int nbr);
int								count_cmd(t_command *cmd);

/*  UTILS2  */
int								ft_strlen_dp(char *s);
void							clear_file(char **filename);
int								str_search(char *big, char *little, int len);
char							*ft_strcpy(char *dst, char *cpy);
char							*ft_strcat(char *dst, char *src);

int								check_file_in2(t_buit_in *exec,
									t_redirections *current);
int								check_file_out2(t_buit_in *exec,
									t_redirections *current);
int								check_file2(t_buit_in *exec, t_command *cmd);

#endif