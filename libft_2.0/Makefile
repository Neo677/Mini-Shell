# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thobenel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/05 20:16:47 by thobenel          #+#    #+#              #
#    Updated: 2024/05/05 20:16:53 by thobenel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I include
RM = rm -f

# Couleurs
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RED = \033[31m
RESET = \033[0m

# Sources
SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
	ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c ft_putchar_fd.c \
	ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_calloc.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_function_printf.c \
	ft_printf.c get_next_line.c get_next_line_utils.c ft_realloc.c

BONUS = ft_lstadd_front.c ft_lstadd_back.c ft_lstnew.c ft_lstlast.c ft_lstsize.c \
	ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstmap.c

# Objects
OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(BONUS:.c=.o)

# Dependencies
DEPS = $(SRCS:.c=.d) $(BONUS:.c=.d)

# Règles
all: $(NAME)
	@echo "$(GREEN)Compilation terminée avec succès !$(RESET)"

$(NAME): $(OBJS)
	@echo "$(YELLOW)Création de la librairie...$(RESET)"
	ar rcs $@ $^

bonus: $(OBJS) $(OBJS_BONUS)
	@echo "$(YELLOW)Ajout des bonus...$(RESET)"
	ar rcs $(NAME) $^

%.o: %.c
	@printf "$(BLUE)[%-50s]$(RESET)\r" "$(patsubst %.c, %.o, $<)"
	@$(CC) $(CFLAGS) -MMD -c $< -o $@
	@printf "$(GREEN)[%-50s]$(RESET)\n" "$(patsubst %.c, %.o, $<)"

-include $(DEPS)

clean:
	@echo "$(RED)Suppression des fichiers objets et dépendances...$(RESET)"
	$(RM) $(OBJS) $(OBJS_BONUS) $(DEPS)

fclean: clean
	@echo "$(RED)Suppression de la librairie...$(RESET)"
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re