# header



NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -I include
LIBFT_DIR = ../libft_v.2.0
LIBFT = $(LIBFT_DIR)/libft.a
READLINE = -lreadline

SRCS = error_token.c \
       free.c \
       main.c \
       prompt.c \
       token_handle.c \
       utils.c \
	   token_utils.c \
	   add_arguments.c \
	   add_redirections.c \
	   create_command.c \
	   split_token.c \
	   parse_token.c \
	   

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