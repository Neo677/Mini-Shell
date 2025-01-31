#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../libft/printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"

# include "../../parsing/minishell.h"  // Include minishell.h to define t_token and t_command

# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

# define ARGC_ERROR "Error : use the right arguments"

typedef struct s_env
{
    char			*key;
    char			*value;
    int				val;
    struct s_env	*next;
}					t_env;

typedef struct s_built_in
{
    int				ac;
    char			**av;
    t_env			*env_cpy;
    t_env			*export_cpy;
    char			**tab;
    char			*input;
    int				cd;
    int				exit;
}					t_buit_in;

typedef struct s_pipex
{
    int						infile;
    int						outfile;
    int						pipefd[2];
    int						len;
    int						i;
    int						*pid;
    int						stdin_fd;
    int						status;
    int						exit_code;
    int						error_outfile;
    int						error;
    char					**cmd;
    char					**paths;
    char					*path;
    char					*paths_cmd;
    char					*path_cmd;
    char					*in;
    char					*out;
    char					**filename_hd;
}							t_pipex;

typedef struct s_token t_token;
typedef struct s_command t_command;



/*  MAIN  */
int					main(int ac, char **av, char **env);

/*  CD  */
int					ft_cd(t_env **env, char *arg);
// char				*cut_path(char *path);

/*  CMD_NODE  */
t_env				*create_node(char *key, char *value);
int					modify_node_value(t_env **env_cpy, char *key,
						char *new_value);
int					delete_node_by_key(t_env **env_cpy, char *key);
int					search_node_and_value(t_env **env, char *key, char *value);
char				*print_node_by_key(t_env **env, char *key);

/*  CPY_ENV  */
int					ft_strlen_c(char *str, int i, char c);
char				**split_in_two(char *str, char c);
t_env				*create_key_value(char *env);
void				copy_env(char **env, t_env **env_cpy);

/*  ECHO  */
int					check_outfile(char *outfile, int fd_stdout,
						char *redirection);
int					check_option(char *option);
void				ft_echo(char **tab);

/*  ENV  */
void				ft_env(t_env **env_cpy);

/*  EXIT  */
int					ft_numeric(char *arg);
long long			ft_atol(char *str, int *error);
int					ft_exit(t_buit_in *exec, char **tab);

/*  EXPORT  */
int					ft_swap(t_env *a, t_env *b);
t_env				*sort_list(t_env **env_cpy);
t_env				**export_cpy(t_env **env_cpy, t_env **cpy_env_cpy);
void				ft_export(t_env **env_cpy1, char *key_value);

/*  FREE  */
void				free_tab(char **tab);
void				free_list(t_env **lst);
void	free_al_builtin(t_buit_in *exec);

/*  INIT  */
void    init_var_builtin(t_buit_in *exec);

/*  PWD  */
void				ft_pwd(t_env **env, int cd);

/*  SIGNAL  */
void				signal_handler(int sig);

/*  SPLIT  */
// int					ft_count(char *s, char c);
// int					ft_len(char *str, char c, int i);
char				**ft_split_init(char *str, char c, char **tab);
char				**ft_split_built(char *str, char c);

/*  UNSET  */
void				ft_unset(t_env **env_cpy, char *key);

/*  UTILS_BUILT_IN  */
int					ft_strlen(char *s);
char				*ft_strdup(char *src);
int					ft_strcmp(char *s1, char *s2);
char				*ft_join(char *join, char *s1, char *s2);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_strchr(const char *s, int c);

int check_file(t_token *token);
char *heredoc_name(int i);
void    init_hd(t_token *token, t_pipex *pipex);
void    clear_file(char **filename);
int check_heredoc(t_token *token, t_pipex *pipex);
void	test_1_2(void);

void	redir_input(t_command *cmd, t_pipex *pipex);
void	child_process(t_pipex *pipex, t_command *cmd, char **envp);

int     check_dir(t_command *cmd);

int ft_strlen_nb(int nb);
char *ft_itoa_exec(int nbr);
int	count_cmd(t_command *cmd);
int ft_strcmp2(char *s1, char *s2);


/*  CHECK_FILE  */
// int							check_outfile(char *outfile);
// int							check_infile(char *infile);
// int							check_file(char *file, int type);
// int							check_redirections(t_redirections	*redirections);

/*  CMD  */
char						*find_cmd(t_pipex *pipex, char *cmd, char **paths);
char						*find_path(t_pipex *pipex, char *cmd, char **envp);
void						execute_cmd(t_pipex *pipex, char *argv,
								char **envp);

/*  FREE  */
// void						free_tab(char **tab);
void						free_all_core(t_pipex *pipex);
void						close_file(t_pipex *pipex);
void						free_error(t_pipex *pipex, char *error,
								int key_error);

/*  INIT_VAR  */
void						init_var(t_pipex *pipex);

/*  INIT  */
// void						init_pipex(t_pipex *pipex, t_command *cmd);

/*  PROCESS  */
void						ft_wait(t_pipex *pipex, int pid[], int len);
void						ft_process(t_pipex *pipex, t_command *cmd, char **envp, int i);
void						ft_pid(t_pipex *pipex, t_command *cmd, char **envp);

/*  SPLIT  */
int							ft_count_pipex(char *s, char c);
int							ft_len_pipex(char *str, char c, int i);
char						**ft_split_dp(t_pipex *pipex, char *str, char c);

/*  UTILS_EROOR */
char						*ft_join_pipex(char *join, char *s1, char *s2);
char						*ft_strjoin_pipex(char *s1, char *s2);
void						write_error(char *cmd);

/*  UTILS */
int							str_search(char *big, char *little, int len);
int							ft_strlen_pipex(char *s);
char						*ft_strcpy(char *dst, char *cpy);
char						*ft_strcat(char *dst, char *src);
void						ft_check_status(t_pipex *pipex);

#endif