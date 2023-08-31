
/*
This header file consist only shared structs.
*/

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include "../libft/libft.h"
#include <execinfo.h>
#include <signal.h>

# define BACKGROUND_MUSIC false
# define MAX_ENEMIES 100
# define LIVES 10
# define WALKING_SPEED 5
# define SIDEWALK_SPEED 3
# define CHANGE_DIRECTION 3
# define E_START_WALK_DIST 5
# define WIDTH 1200
# define HEIGTH 600
# define PI 3.141592653589793238462643383279502884197
# define ENEMY_LIVES 3
# define N_TEX 10
# define VIEW_ANGLE 45
# define RAY_ANGLE (VIEW_ANGLE * PI / 180 / WIDTH)
# define E_TEX_ITER 8
# define ENEMY_HEIGHT 0.8f

typedef uint32_t	color;

typedef enum e_tex
{
	NORTH_T,
	SOUTH_T,
	EAST_T,
	WEST_T,
	DOOR_T,
	ENEMY_T,
	HEART_RED_T,
	HEART_RED_BLACK_T,
	HEART_BLACK_T,
	GUN_T,
}	t_tex;

/*
For building a map, please, use:
0 or space for floor
1 for walls
N, S, W or E for player's start position and view
H for closed
X for enemy
*/

typedef enum e_map_char
{
	SPACE,
	WALL,
	PLAYER,
	CLOSED_DOOR,
	OPENED_DOOR,
	ENEMY,
	TERMINAL,
	ERROR,
}	t_map_char;

typedef struct s_map
{
	struct s_frame		*frame;
	struct s_ray		*ray;
	struct s_character	*enemy[MAX_ENEMIES + 1];
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*minimap;
	mlx_texture_t		*tex[N_TEX];
	// mlx_texture_t		*enemy_tex;
	color				floor;
	color				ceiling;
	t_map_char			**co;
	int					map_height;
	int					map_width;
	double				px;
	double				py;
	double				pa;
	double				pdx;
	double				pdy;
	double				p_radius;
	int					mm_radius;
	int					mm_square;
	int					mouse_pos;
	bool				shoot;
	int					lives;
	int					pid;
}	t_map;

typedef struct s_frame
{
	unsigned int	counter;
	int	n_backstep;
	int	e_tex;
} t_frame;

void	print_map(t_map *map);

#endif
