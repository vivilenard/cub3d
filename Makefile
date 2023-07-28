# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 13:44:57 by vlenard           #+#    #+#              #
#    Updated: 2023/07/28 18:33:13 by ekulichk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
FLAGS = -Wall -Werror -Wextra

ifeq ($(USER), elenakulichkova)
MLX = MLX42/build/libmlx42.a -I include -lglfw -L/"opt/homebrew/Cellar/glfw/3.3.8/lib/"
else
MLX = MLX42/build/libmlx42.a -I include -lglfw -L "/Users/vlenard/.brew/opt/glfw/lib/"
endif

SRC = main.c raycaster.c init_data.c utils.c parser.c map_to_coordinate.c \
	minimap.c help_functions.c key_bindings.c texture.c
# OBJ = $(SRC:.c=.o)
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
LIBFT = libft/libft.a

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(MLX) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	cd libft && make && make clean

$(OBJ_DIR)/%.o: %.c 
	@cc $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f ./$(NAME)

re: fclean all

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

build:
	@git submodule update --init
	@git clone https://github.com/codam-coding-college/MLX42.git
	@cd MLX42 && cmake -B build && cmake --build build -j4

simple:
	make re && make clean && ./cub3d maps/simple.cub