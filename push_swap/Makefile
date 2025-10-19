# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/16 20:55:15 by otlacerd          #+#    #+#              #
#    Updated: 2025/10/19 05:35:36 by otlacerd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
BUILD_DIR = build
INCLUDES = -I.

all: $(NAME)

SRCS = push_swap.c \
       modules/parsing/creating_list.c \
	   modules/parsing/parsing_utils.c \
	   modules/parsing/check_numbers.c \
	   modules/core/core_utils.c \
	   modules/data/data.c \
	   modules/list_tools/lstadd_back.c \
	   modules/list_tools/lstadd_front.c \
	   modules/list_tools/lstclear.c \
	   modules/list_tools/lstnew.c \
	   modules/list_tools/lstsize.c \
	   modules/operations/push.c \
	   modules/operations/reverse_rotate.c \
	   modules/operations/rotate.c \
	   modules/operations/swap.c \
# 	   modules/list_tools/list_tools_utils.c \
# 	   modules/list_tools/lstdelone.c \
# 	   modules/list_tools/lstiter.c \
# 	   modules/list_tools/lstlast.c \
# 	   modules/list_tools/lstmap.c \

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
