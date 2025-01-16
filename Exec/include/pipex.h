
#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/printf/ft_printf.h"
// # include "../libft/get_next_line/get_next_line.h"
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
}							t_pipex;

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
}							t_token_arg;

/*
		chain list for handle the token
		type ==  type du token in enum ⬆️
		valeur == valeur du token
		next == ptr for next token (chain list)
*/

typedef struct s_token
{
	t_token_arg				type;
	char					*value;
	struct s_token			*next;
}							t_token;

typedef struct s_redirections
{
	int						type;
	char					*file;
	struct s_redirections	*next;
}							t_redirections;

/*
		main structure for the command
	char **arg == tab de tab for the arguments of the command
	t_redirections *redirections == list of redirections associed to the command
	int 	p_pipe ==  1 si un pipe suit cette commande
	struct s_command *next == ptr for the next command (pipeline)
*/
typedef struct s_command
{
	char					**arg;
	t_redirections			*redirections;
	int						p_pipe;
	struct s_command		*next;
}							t_command;

/*  CHECK_FILE  */
int							check_outfile(char *outfile);
int							check_infile(char *infile);
int							check_file(char *file, int type);
int							check_redirections(t_redirections	*redirections);

/*  CMD  */
char						*find_cmd(t_pipex *pipex, char *cmd, char **paths);
char						*find_path(t_pipex *pipex, char *cmd, char **envp);
void						execute_cmd(t_pipex *pipex, char *argv,
								char **envp);

/*  FREE  */
void						free_tab(char **tab);
void						free_all(t_pipex *pipex);
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
int							ft_count(char *s, char c);
int							ft_len(char *str, char c, int i);
char						**ft_split(t_pipex *pipex, char *str, char c);

/*  UTILS_EROOR */
char						*ft_join(char *join, char *s1, char *s2);
char						*ft_strjoin(char *s1, char *s2);
void						write_error(char *cmd);

/*  UTILS */
int							str_search(char *big, char *little, int len);
int							ft_strlen(char *s);
char						*ft_strcpy(char *dst, char *cpy);
char						*ft_strcat(char *dst, char *src);
void						ft_check_status(t_pipex *pipex);

#endif