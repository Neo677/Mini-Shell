CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -lreadline
SRCS = built_in.c \
cd.c \
cmd_node.c \
cpy_env.c \
echo.c \
env.c \
exit.c \
export.c \
free.c \
init.c \
pwd.c \
signal.c \
split.c \
unset.c \
utils_built_in.c \
utils.c \


OBJS = $(SRCS:.c=.o)

NAME = minishell

FT_PRINTF = ../libft/printf/libftprintf.a

INCLUDES =  -I../libft/printf -I../include

MLX_FLAGS = -L../libft/printf -lftprintf -lreadline

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