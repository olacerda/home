# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otlacerd <otlacerd@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/14 06:10:07 by otlacerd          #+#    #+#              #
#    Updated: 2025/10/14 06:48:27 by otlacerd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
BUILD_DIR = build
MLX_DIR = MiniLibX/minilibx-linux
INCLUDES = -I. -I$(MLX_DIR)
USER_DIR = modules/user_info
USER_NAME_FILE = $(USER_DIR)/user_name.ber
COMP_NUM_FILE = $(USER_DIR)/computer_number.ber

all: user_info $(NAME)

user_info: FORCE
	@echo -n "$$(whoami)" > $(USER_NAME_FILE)
	@echo -n "$$(hostname | cut -d'.' -f1)%" > $(COMP_NUM_FILE)

FORCE:

SRCS = so_long.c \
       modules/core_game/core_game.c \
       modules/core_game/core_game_utils.c \
       modules/core_game/hook_inputs.c \
       modules/core_game/info_update.c \
       modules/core_game/movement.c \
       modules/core_game/player_box.c \
       modules/core_game/undefined_behavior.c \
       modules/data/core_data.c \
       modules/data/delete_data.c \
       modules/graphic/core_animations.c \
       modules/graphic/create_images.c \
       modules/graphic/fill_buffers.c \
       modules/graphic/flush_imgs.c \
       modules/graphic/sub_animations.c \
       modules/parsing/check_elements.c \
       modules/parsing/check_map_info.c \
       modules/parsing/check_path.c \
       modules/parsing/check_walls.c \
       modules/parsing/core_parsing.c \
       modules/parsing/parsing_utils.c \
       modules/terminal/core_terminal.c \
       modules/terminal/general_messages.c \
       modules/terminal/message_cat.c \
       modules/terminal/root_messages.c \
       modules/terminal/root_state.c \
       modules/terminal/sub_messages.c \
       modules/terminal/terminal_hooks.c \
       modules/terminal/terminal_sub_hooks.c \
       modules/terminal/terminal_utils.c

OBJS = $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L $(MLX_DIR) -lmlx -lXext -lX11 -lm

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(BUILD_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
