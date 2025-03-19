# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:24:52 by thobenel          #+#    #+#              #
#    Updated: 2025/03/19 18:34:16 by dpascal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g #-ltinfo
CFLAGS = -Wall -Wextra -Werror -I include #-fsanitize=leak
LIBFT_DIR = libft_2.0
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR_MATE = exec/libft/printf
LIBFT_MATE = $(LIBFT_DIR_MATE)/libftprintf.a
READLINE = -lreadline

SRCS =	parsing/add_arguments.c \
		parsing/init_parsing.c \
		parsing/init_parsing_two.c \
		parsing/init_parse_help.c \
		parsing/main.c \
		parsing/main_use.c \
		parsing/add_redirections.c \
		parsing/create_command.c \
		parsing/env_var_dct.c \
		parsing/free.c \
		parsing/handle_error.c \
		parsing/handle_error_2.c \
		parsing/handle_quotes_d.c \
		parsing/handle_quotes_s.c \
		parsing/expander.c \
		parsing/expander_double.c \
		parsing/eof_quote.c \
		parsing/expander_use.c \
		parsing/shell_process.c \
		parsing/parse_token.c \
		parsing/prompt.c \
		parsing/process_token.c \
		parsing/handle_env.c \
		parsing/handle_env_two.c \
		parsing/handle_env_use.c \
		parsing/handle_quote.c \
		parsing/build_quote.c \
		parsing/handle_word.c \
		parsing/handle_word_expand.c \
		parsing/split_token.c \
		parsing/token_handle.c \
		parsing/token_utils.c \
		parsing/utils_main.c \
		parsing/utils.c \
		parsing/utils_2.c \
		parsing/syntax_before.c \
		parsing/syntax_before_two.c \
		parsing/start_minishell.c \
		parsing/valid_token.c \
		parsing/valid_token_two.c \
		parsing/replace_env.c \
		parsing/creat_command_utils.c \
		parsing/quote_utils.c \
		parsing/pid.c \
		parsing/create_command_use.c \
		exec/built-in/cd.c \
		exec/built-in/cmd_node.c \
		exec/built-in/cpy_env.c \
		exec/built-in/echo.c \
		exec/built-in/env.c \
		exec/built-in/exit.c \
		exec/built-in/export.c \
		exec/built-in/export2.c \
		exec/built-in/export3.c \
		exec/built-in/free_bh.c \
		exec/built-in/init.c \
		exec/built-in/pwd.c \
		exec/built-in/split_var.c \
		exec/built-in/split.c \
		exec/built-in/unset.c \
		exec/built-in/utils_built_in.c \
		exec/built-in/utils_cmd_node.c \
		exec/built-in/utils_export.c \
		exec/core/builtin.c \
		exec/core/change_dir.c \
		exec/core/check_dir.c \
		exec/core/cmd.c \
		exec/core/free_exec.c \
		exec/core/here_doc.c \
		exec/core/init_var.c \
		exec/core/process.c \
		exec/core/redir.c \
		exec/core/signal.c \
		exec/core/split.c \
		exec/core/utils_cmd.c \
		exec/core/utils_error.c \
		exec/core/utils_heredoc.c \
		exec/core/utils_process.c \
		exec/core/utils.c \
		exec/core/utils2.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBFT_MATE)
	@echo "Lien des objets pour créer $(NAME)..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBFT_MATE) $(READLINE)

$(LIBFT):
	@echo "Compilation de la libft..."
	$(MAKE) -C $(LIBFT_DIR)

$(LIBFT_MATE):
	@echo "Compilation de la libft du Mate..."
	$(MAKE) -C $(LIBFT_DIR_MATE)

%.o: %.c
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Suppression des fichiers objets..."
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(LIBFT_DIR_MATE) clean

fclean: clean
	@echo "Suppression de $(NAME) et de la libft..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR_MATE) fclean

re: fclean all

.PHONY: all clean fclean re