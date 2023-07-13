# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 13:44:57 by vlenard           #+#    #+#              #
#    Updated: 2023/07/13 15:24:32 by vlenard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
FLAGS = -Wall -Werror -Wextra
MLX = MLX42/build/libmlx42.a -I include -lglfw -L "/Users/vlenard/.brew/opt/glfw/lib/"
SRC = main.c init_data.c utils.c parser.c map_to_coordinate.c minimap.c help_functions.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(MLX) $(OBJ) $(LIBFT) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ./$(NAME)

re: fclean all

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@