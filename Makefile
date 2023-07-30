
NAME = cub3d
CC = cc
FLAGS = -Wall -Werror -Wextra

GREEN = \033[0;32m
RESET = \033[0m

ifeq ($(USER), elenakulichkova)
MLX = MLX42/build/libmlx42.a -I include -lglfw -L/"opt/homebrew/Cellar/glfw/3.3.8/lib/"
else
MLX = MLX42/build/libmlx42.a -I include -lglfw -L "/$(HOME)/.brew/opt/glfw/lib/"
endif

SRC =	main.c\
		raycaster.c\
		init_data.c\
		utils.c\
		parser.c\
		map_to_coordinate.c\
		minimap.c\
		help_functions.c\
		key_bindings.c\
		texture.c

OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
LIBFT = libft/libft.a

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(MLX) $(OBJ) $(LIBFT) -o $(NAME)
	@printf "$(GREEN)Compiled$(RESET)\n"

$(LIBFT):
	@cd libft && make && make clean

$(OBJ_DIR)/%.o: %.c 
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@printf "Cleaned\n"

fclean: clean
	@rm -f ./$(NAME)

re: fclean all

%.o: %.c
	$(CC) $(FLAGS) -c $^ -o $@

build:
	@git submodule update --init
	@cd MLX42 && cmake -B build && cmake --build build -j4

simple:
	make re && make clean && ./cub3d maps/simple.cub

.PHONY: all clean fclean re build simple