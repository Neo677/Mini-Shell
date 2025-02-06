#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "../libft/printf/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

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
}					t_buit_in;

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
int 				search_by_key(t_env **env, char *key);
char				*print_node_by_key(t_env **env, char *key);

/*  CPY_ENV  */
int					ft_strlen_c(char *str, int i, char c);
char				**split_in_two(char *str, char c);
t_env				*create_key_value(char *env);
void				copy_env(char **env, t_env **env_cpy);
char *parse_value(char *input);
int check_value(char *str);

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
void				ft_export(t_env **env_cpy1, char **key_value);

/*  FREE  */
void				free_tab(char **tab);
void				free_list(t_env **lst);
void 				free_env_list(t_env *head);
void				free_all(t_buit_in *exec);

/*  INIT  */
void    			init_var(t_buit_in *exec);

/*  PWD  */
void				ft_pwd(t_env **env, int cd);

/*  SIGNAL  */
void				signal_handler(int sig);

/*  SPLIT  */
int					ft_count(char *s, char c);
int					ft_len(char *str, char c, int i);
char				**ft_split_init(char *str, char c, char **tab);
char				**ft_split_built(char *str, char c);
char    *split_export(char *str);

/*  UNSET  */
void				ft_unset(t_env **env_cpy, char *key);

/*  UTILS_BUILT_IN  */
int					ft_strlen(char *s);
char				*ft_strdup(char *src);
int					ft_strcmp(char *s1, char *s2);
char				*ft_join(char *join, char *s1, char *s2);
char				*ft_strjoin(char *s1, char *s2);
// char				*ft_strchr(const char *s, int c);

/*  UTILS  */
int skip_built(char *str);
int	count_export_var(char *str);
char  **tab_export(char *str);

#endif