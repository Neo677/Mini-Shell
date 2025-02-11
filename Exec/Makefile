
CC = gcc -g
CFLAGS = -Wall -Wextra -Werror
SRCS = core/pipex.c \
core/cmd.c \
core/utils.c \
core/free.c \
core/split.c \
core/process.c \
core/init.c \
core/init_var.c \
core/utils_error.c \
core/here_doc.c \
core/check_file.c \
libft/get_next_line/get_next_line.c \
libft/get_next_line/get_next_line_utils.c \


OBJS = $(SRCS:.c=.o)

NAME = minishell

FT_PRINTF = ./libft/printf/libftprintf.a

INCLUDES =  -I./libft/printf -I./include

MLX_FLAGS = -L./libft/printf -lftprintf

all: $(NAME)

$(NAME): $(OBJS) $(FT_PRINTF)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all