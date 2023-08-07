
NAME = cub3D
CC = cc
FLAGS = -Wall -Werror -Wextra 

GREEN = \033[0;32m
RESET = \033[0m

ifeq ($(USER), elenakulichkova)
MLX = MLX42/build/libmlx42.a -I include -lglfw -L/"opt/homebrew/Cellar/glfw/3.3.8/lib/"
else
MLX = MLX42/build/libmlx42.a -I include -lglfw -L "/$(HOME)/.brew/opt/glfw/lib/"
endif
SAN_LDFLAG = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize

SRC =	main.c\
		parser/identifiers.c\
		parser/init_data.c\
		parser/map_to_coordinate.c\
		parser/parser.c\
		parser/read_map.c\
		parser/read_map_utils.c\
		parser/utils.c\
		visuals/display.c \
		visuals/raycaster.c\
		visuals/dda.c\
		visuals/minimap.c\
		visuals/help_functions.c\
		visuals/key_bindings.c\
		visuals/mouse_bindings.c\
		visuals/texture.c\
		enemy/init_enemies.c\
		enemy/calibrate_enemies.c\
		enemy/draw_enemies.c

OBJ_DIR = obj
VISUALS_DIR = /visuals
PARSE_DIR = /parser
ENEMY_DIR = /enemy
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
LIBFT = libft/libft.a

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(VISUALS_DIR)
	@mkdir -p $(OBJ_DIR)$(PARSE_DIR)
	@mkdir -p $(OBJ_DIR)$(ENEMY_DIR)

$(NAME): $(OBJ_DIR) $(OBJ) $(LIBFT)
	@$(CC) $(FLAGS) $(MLX) $(OBJ) $(LIBFT) -o $(NAME) #$(SAN_LDFLAG)
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
	make re && make clean && ./cub3D maps/simple.cub
enemy:
	./cub3D maps/enemy.cub
.PHONY: all clean fclean re build simple