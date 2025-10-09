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
LDLIBS = $(LIBFT) -lreadline

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
else
    MLX_FLAGS = -Lmlx -lmlx -lX11 -lXext -lm
endif

SRCS = main.c \
	 player.c \
	 raycast/distance.c \
	 raycast/raycast.c \
	 raycast/draws.c \
	 exit_game.c \
	 parser/main_parse.c \
	 textures.c


OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

# no topo (ou onde preferir)
MAP ?= maps/crazy8.cub


vpath %.c $(SRC_DIR) $(SRC_DIR)/parser $(SRC_DIR)

LIBFT = $(LIBFT_DIR)/libft.a

all: $(LIBFT) $(NAME)

# val: valgrind --leak-check=full --show-leak-kinds=all ./cub3d

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) $(MLX_FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# valgrind:
# 	-$(VALGRIND) ./$(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) $(MAP)

valgrind: all
	@/bin/valgrind -q \
				--leak-check=full \
				--show-leak-kinds=all \
				--track-origins=yes \
				--track-fds=yes \
				--trace-children=yes \
				--trace-children-skip='*/bin/*,*/sbin/*,/usr/bin/*' \
				./${NAME}


re: fclean all

.PHONY: all clean fclean re valgrind
