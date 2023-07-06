# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/05 13:44:57 by vlenard           #+#    #+#              #
#    Updated: 2023/07/06 14:07:48 by vlenard          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
CC = cc
FLAGS = -Wall -Werror -Wextra
MLX = MLX42/build/libmlx42.a -I include -lglfw -L "/Users/vlenard/.brew/opt/glfw/lib/"
SRC = main.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(MLX) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f ./$(NAME)

re: fclean all

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@