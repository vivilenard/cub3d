
#ifndef MAIN_H
# define MAIN_H

/*
This header file consist only shared structs.
We should rename it (probably).
*/
# define MAX_ENEMIES 6
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
}	t_side;

typedef enum e_map_component
{
	SPACE = '0', // 0
	WALL = '1', // 1
	PLAYER, // N, S, W, E
	CLOSED_DOOR = 'D', // H
	OPENED_DOOR = 'd', // I
	ERROR,
}	t_map_component;

typedef struct s_map
{
	struct s_ray		*ray;
	struct s_character	*enemy[MAX_ENEMIES];
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*minimap;
	mlx_texture_t		*tex[N_TEX];	//space for 10 textures -- dont know how much we need
	mlx_texture_t		*enemy_tex;
	color				floor;
	color				ceiling;
	char				**co;
	int					map_height;
	int					map_width;
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
