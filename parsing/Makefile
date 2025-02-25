# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dpascal <dpascal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:24:52 by thobenel          #+#    #+#              #
#    Updated: 2025/02/13 22:25:06 by dpascal          ###   ########.fr        #
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
		parse_token.c \
		prompt.c \
		init_parsing.c \
		process_token.c \
		handle_env.c \
		handle_word.c \
		split_token.c \
		token_handle.c \
		token_utils.c \
		utils_main.c \
		utils.c \
		syntax_before.c \
		start_minishell.c \
		valid_token.c \
		replace_env.c \
		creat_command_utils.c \
		matrix.c \
		quote_utils.c \
		pid.c \
		create_command_use.c \
		../exec/core/check_file.c \
		../exec/core/cmd.c \
		../exec/core/exec.c \
		../exec/core/utils.c \
		../exec/core/free_exec.c \
		../exec/core/split.c \
		../exec/core/process.c \
		../exec/core/init_var.c \
		../exec/core/utils_error.c \
		../exec/core/here_doc.c \
		../exec/built-in/cd.c \
		../exec/built-in/cmd_node.c \
		../exec/built-in/cpy_env.c \
		../exec/built-in/init.c \
		../exec/built-in/echo.c \
		../exec/built-in/env.c \
		../exec/built-in/exit.c \
		../exec/built-in/export.c \
		../exec/built-in/free_bh.c \
		../exec/built-in/pwd.c \
		../exec/built-in/split.c \
		../exec/built-in/unset.c \
		../exec/built-in/utils_built_in.c \
		../exec/built-in/utils.c \
		../exec/built-in/signal.c

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