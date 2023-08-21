
#ifndef MAIN_H
# define MAIN_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

/*
This header file consist only shared structs.
We should rename it (probably).
*/

# define MAX_ENEMIES 6
# define N_TEX 7
# define WIDTH 1200
# define HEIGTH 600
# define PI 3.141592653589793238462643383279502884197
# define N_ENEMIES 6
# define N_TEX 7
# define VIEW_ANGLE 1.15 //=66 degree
# define RAY_ANGLE (VIEW_ANGLE / WIDTH)


typedef uint32_t	color;

typedef enum e_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR,
}	t_side;

typedef enum e_map_char
{
	SPACE, // 0
	WALL, // 1
	PLAYER, // N, S, W, E
	CLOSED_DOOR, // H
	OPENED_DOOR, // I
	ENEMY, // X
	TERMINAL,
	ERROR,
}	t_map_char;

typedef struct s_map
{
	struct s_ray		*ray;
	struct s_character	*enemy[MAX_ENEMIES];
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*minimap;
	mlx_texture_t		*tex[N_TEX];	// done in parser
	mlx_texture_t		*enemy_tex; 	// done in parser
	color				floor; 			// done in parser
	color				ceiling; 		// done in parser
	// char				**co; 			// done in parser
	t_map_char			**co;
	int					map_height; 	// done in parser
	int					map_width; 		// done in parser
	double				px;				// player position done in parser
	double				py;
	double				pa;				// player angle done in parser
	double				pdx; 			// player direction vector done in parser
	double				pdy;
	double				p_radius;		// size of player in minimap done in parser
	int					mm_radius;	//size of minimap
	int					mm_square;	//size of a tile
	int					mouse_pos;
}	t_map;

void	print_map(t_map *map);

#endif
