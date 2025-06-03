CC = cc
CFLAGS = -Wall -Wextra -Werror -g

SRCS = main.c \
	parsing/map_parser.c parsing/map_parser_config.c parsing/map_grid_parser.c parsing/map_validator.c \
	parsing/map_debug.c init_window.c draw_walls.c init_structs.c update_player.c draw_background.c camera_rotate.c \
	key_handler.c player_movement.c free_memory.c parsing/map_parsing_utils.c \
	get_next_line/get_next_line.c utils.c

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
MLX_A = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

OBJS = $(SRCS:.c=.o)
NAME = cub3d

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
