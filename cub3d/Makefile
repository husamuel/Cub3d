# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: diolivei <diolivei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/04 17:34:15 by diolivei          #+#    #+#              #
#    Updated: 2025/07/11 16:30:12 by diolivei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = parsing/map_debug_utils.c parsing/map_debug.c parsing/map_grid_parser.c parsing/map_grid_utils.c parsing/map_parser_config.c parsing/map_parser.c parsing/map_parsing_utils.c parsing/map_validator_utils.c parsing/map_validator.c \
src/camera_rotate.c src/draw_background.c src/draw_walls_utils.c src/draw_walls_utils2.c src/draw_walls.c src/free_memory.c src/init_structs.c src/init_window.c src/key_handler.c src/main_utils.c src/main.c src/player_movement.c src/update_player_utils.c src/update_player.c src/utils.c

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX_A = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

OBJS = $(SRCS:.c=.o)
NAME = cub3D

all: $(LIBFT_A) $(MLX_A) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(MLX_A):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(MLX_DIR)/*.o $(MLX_DIR)/libmlx.a

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
