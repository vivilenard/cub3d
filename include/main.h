
#ifndef MAIN_H
# define MAIN_H

/*
This header file consist only shared structs.
We should rename it (probably).
*/
# define N_ENEMIES 6
# define N_TEX 6

# include "../MLX42/include/MLX42/MLX42.h"

typedef uint32_t	color;

typedef enum e_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	DOOR,
	NONE,
}	t_side;

// typedef enum e_map_char
// {
// 	SPACE = '0', // 0
// 	WALL = '1', // 1
// 	PLAYER, // N, S, W, E
// 	CLOSED_DOOR = 'D', // H
// 	OPENED_DOOR = 'd', // I
// 	ENEMY, // X
// 	ERROR,
// }	t_map_char;

typedef enum e_map_char
{
	SPACE, // 0
	WALL, // 1
	PLAYER, // N, S, W, E
	CLOSED_DOOR, // H
	OPENED_DOOR, // I
	ENEMY, // X
	ERROR,
}	t_map_char;

typedef struct s_map
{
	struct s_ray		*ray;
	struct s_character	*enemy[N_ENEMIES];
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*minimap;
	mlx_texture_t		*tex[N_TEX];	//THIS		//space for 10 textures -- dont know how much we need
	mlx_texture_t		*enemy_tex; 	//THIS
	color				floor; 			//THIS
	color				ceiling; 		//THIS
	// char				**co; 			//THIS
	t_map_char			**co;
	int					map_height; 	//THIS
	int					map_width; 		//THIS
	double				px;			//player position
	double				py;
	double				pa;			//player angle
	double				pdx; 		//player direction vector
	double				pdy;
	double				p_radius;	//size of player in minimap
	int					mm_radius;	//size of minimap
	int					mm_square;	//size of a tile
	int					mouse_pos;
}	t_map;

#endif
