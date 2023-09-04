
NAME = cub3D
CC = cc 
CFLAGS = -Wall -Werror -Wextra

GREEN = \033[0;32m
RESET = \033[0m

ifeq ($(USER), elenakulichkova)
MLX = MLX42/build/libmlx42.a -I include -lglfw -L/"opt/homebrew/Cellar/glfw/3.3.8/lib/"
else
MLX = MLX42/build/libmlx42.a -I include -lglfw #-L "/$(HOME)/.brew/opt/glfw/lib/"
endif
SAN_LDFLAG = -L../LeakSanitizer -llsan -lc++ -Wno-gnu-include-next -I ../LeakSanitize

ifndef LEN
	CFLAGS += -Wall -Werror -Wextra
endif

ifdef DEBUG
	CFLAGS += -g -fsanitize=address
endif

SRC =	main.c\
		free.c\
		parser/color.c\
		parser/create_map.c\
		parser/identifiers.c\
		parser/init_data.c\
		parser/map_verify.c\
		parser/parser_utils.c\
		parser/parser.c\
		parser/read_map.c\
		visuals/display.c \
		visuals/raycaster.c\
		visuals/math.c\
		visuals/dda.c\
		visuals/minimap.c\
		visuals/door.c\
		visuals/draw_functions.c\
		visuals/draw_minimap.c\
		visuals/help_functions.c\
		visuals/hook_keys.c\
		visuals/hook_mouse.c\
		visuals/texture.c\
		visuals/attacks.c\
		visuals/display_extras.c\
		enemy/init_enemies.c\
		enemy/calibrate_enemies.c\
		enemy/draw_enemies.c\
		enemy/enemy_utils.c

OBJ_DIR = obj
VISUALS_DIR = /visuals
PARSE_DIR = /parser
ENEMY_DIR = /enemy
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
LIBFT = libft/libft.a
HEADERS = include/cub3d.h include/display.h include/parser.h

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(MLX) $(OBJ) $(LIBFT) -o $(NAME) #$(SAN_LDFLAG) #$(if $(DEBUG),-fsanitize=address, )
	@printf "$(GREEN)Compiled$(RESET)\n"

$(LIBFT):
	@cd libft && make DEBUG=$(DEBUG) && make clean

$(OBJ_DIR)/%.o: %.c $(HEADERS) Makefile | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@cc $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@printf "Cleaned\n"

fclean: clean
	@cd libft && make fclean
	@rm -f ./$(NAME)

re: fclean all

build:
	@git submodule update --init
	@cd MLX42 && cmake $(if $(DEBUG),-DDEBUG=1, ) -B build && cmake --build build -j4

simple:
	make re && make clean && ./cub3D maps/simple.cub
enemy:
	./cub3D maps/enemy.cub
.PHONY: all clean fclean re build simple