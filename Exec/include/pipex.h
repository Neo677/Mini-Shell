
#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/printf/ft_printf.h"
# include "../libft/get_next_line/get_next_line.h"
# include "../../parsing/minishell.h"
# include "../built-in/built_in.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define ARGC_ERROR "Error : use the right arguments"

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