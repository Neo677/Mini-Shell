
NAME = minishell_exec
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -I include #-fsanitize=leak
LIBFT_DIR = ../libft_2.0
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =	core/pipex.c \
	core/cmd.c \
	core/utils.c \
	core/free.c \
	core/split.c \
	core/process.c \
	core/init.c \
	core/init_var.c \
	core/utils_error.c \
	core/here_doc.c \
	built_in/cd.c \
	built_in/cmd_node.c \
	built_in/cpy_env.c \
	built_in/echo.c \
	built_in/env.c \
	built_in/exit.c \
	built_in/export.c \
	built_in/free.c \
	built_in/pwd.c \
	built_in/split.c \
	built_in/unset.c \
	built_in/utils_built_in.c \



OBJS = $(SRCS:.c=.o)

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

