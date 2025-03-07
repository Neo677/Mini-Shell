# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:24:52 by thobenel          #+#    #+#              #
#    Updated: 2025/03/06 14:18:58 by dpascal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc -g #-ltinfo
CFLAGS = -Wall -Wextra -Werror -I include #-fsanitize=leak
LIBFT_DIR = ../libft_2.0
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_DIR_MATE = ../exec/libft/printf
LIBFT_MATE = $(LIBFT_DIR_MATE)/libftprintf.a
READLINE = -lreadline

SRCS =	add_arguments.c \
		add_redirections.c \
		create_command.c \
		env_var_dct.c \
		free.c \
		handle_error.c \
		handle_error_2.c \
		handle_quotes_d.c \
		handle_quotes_s.c \
		expander.c \
		expander_double.c \
		eof_quote.c \
		expander_use.c \
		main.c \
		main_use.c \
		parse_token.c \
		prompt.c \
		init_parsing.c \
		process_token.c \
		handle_env.c \
		handle_quote.c \
		handle_word.c \
		split_token.c \
		token_handle.c \
		token_utils.c \
		utils_main.c \
		utils_main2.c \
		utils.c \
		utils_2.c \
		syntax_before.c \
		syntax_before_two.c \
		start_minishell.c \
		valid_token.c \
		valid_token_two.c \
		replace_env.c \
		creat_command_utils.c \
		matrix.c \
		quote_utils.c \
		pid.c \
		create_command_use.c \
		../exec/built-in/cd.c \
		../exec/built-in/cmd_node.c \
		../exec/built-in/cpy_env.c \
		../exec/built-in/echo.c \
		../exec/built-in/env.c \
		../exec/built-in/exit.c \
		../exec/built-in/export.c \
		../exec/built-in/export2.c \
		../exec/built-in/export3.c \
		../exec/built-in/free_bh.c \
		../exec/built-in/init.c \
		../exec/built-in/pwd.c \
		../exec/built-in/signal.c \
		../exec/built-in/split_var.c \
		../exec/built-in/split.c \
		../exec/built-in/unset.c \
		../exec/built-in/utils_built_in.c \
		../exec/built-in/utils_cmd_node.c \
		../exec/built-in/utils_export.c \
		../exec/core/builtin.c \
		../exec/core/check_file.c \
		../exec/core/check_file2.c \
		../exec/core/cmd.c \
		../exec/core/free_exec.c \
		../exec/core/here_doc.c \
		../exec/core/init_var.c \
		../exec/core/process.c \
		../exec/core/process2.c \
		../exec/core/redir.c \
		../exec/core/split.c \
		../exec/core/utils_error.c \
		../exec/core/utils.c \
		../exec/core/utils2.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBFT_MATE)
	@echo "Lien des objets pour créer $(NAME)..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(LIBFT_MATE) $(READLINE)

$(LIBFT):
	@echo "Compilation de la libft..."
	make -C $(LIBFT_DIR)

$(LIBFT_MATE):
	@echo "Compilation de la libft du Mate..."
	make -C $(LIBFT_DIR_MATE)

%.o: %.c
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Suppression des fichiers objets..."
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) $(LIBFT_DIR_MATE)  clean

fclean: clean
	@echo "Suppression de $(NAME) et de la libft..."
	rm -f $(NAME)
	make -C $(LIBFT_DIR) $(LIBFT_DIR_MATE) fclean

re: fclean all

.PHONY: all clean fclean re