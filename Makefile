# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/28 18:48:43 by marvin            #+#    #+#              #
#    Updated: 2025/09/28 18:48:43 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc

SRC_DIR = srcs
OBJ_DIR = obj
INCLUDES_DIR = includes
LIBFT_DIR = libft

CFLAGS = -Wall -Wextra -Werror -g3 -I$(INCLUDES_DIR)
LDFLAGS =

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
else
	MLX_FLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm
endif

SRCS = main.c \
	raycast/distance.c \
	raycast/raycast.c \
	raycast/draws.c \
	exit_game.c \
	parser/main_parse.c \
	read/read_map.c \
	read/utils_read.c \
	vignette/vignette.c \
	player/player.c \
	player/keyboard.c \
	textures.c

SRCS_FULL := $(addprefix $(SRC_DIR)/,$(SRCS))
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS_FULL))

MAP ?= maps/crazy8.cub

LIBFT = $(LIBFT_DIR)/libft.a

.PHONY: all clean fclean re valgrind libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJS) $(MLX_FLAGS) $(LIBFT) -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	-rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	-rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

valgrind: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(MAP)
