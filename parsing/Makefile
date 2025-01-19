# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thobenel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/12 17:24:52 by thobenel          #+#    #+#              #
#    Updated: 2024/12/12 17:24:55 by thobenel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables principales
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include #-fsanitize=leak
LIBFT_DIR = ../libft_2.0
LIBFT = $(LIBFT_DIR)/libft.a
READLINE = -lreadline

# Sources et objets
SRCS =  add_arguments.c \
        add_redirections.c \
        create_command.c \
		env_var_dct.c \
        free.c \
		handle_error.c \
		handle_error_2.c \
		handle_quotes.c \
        main.c \
        parse_token.c \
        prompt.c \
        split_token.c \
        token_handle.c \
        token_utils.c \
        utils_main.c \
        utils.c \
		syntax_before.c \
		start_minishell.c \
		valid_token.c \
		double_quote.c \


OBJS = $(SRCS:.c=.o)

# Règles principales
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "Lien des objets pour créer $(NAME)..."
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)

$(LIBFT):
	@echo "Compilation de la libft..."
	make -C $(LIBFT_DIR)

%.o: %.c
	@echo "Compilation de $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Suppression des fichiers objets..."
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "Suppression de $(NAME) et de la libft..."
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
