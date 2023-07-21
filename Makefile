# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 13:44:57 by vlenard           #+#    #+#              #
#    Updated: 2023/07/21 16:46:04 by vlenard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
FLAGS = -Wall -Werror -Wextra
MLX = MLX42/build/libmlx42.a -I include -lglfw -L "/Users/vlenard/.brew/opt/glfw/lib/"
SRC = main.c raycaster.c init_data.c utils.c parser.c map_to_coordinate.c \
	minimap.c help_functions.c key_bindings.c texture.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) $(MLX) $(OBJ) $(LIBFT) -o $(NAME)

$(LIBFT):
	cd libft && make && make clean

clean:
	rm -f $(OBJ)

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