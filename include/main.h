
#ifndef MAIN_H
# define MAIN_H

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

/*
This header file consist only shared structs.
We should rename it (probably).
*/

# define MAX_ENEMIES 10
# define LIVES 1000
# define N_TEX 7
# define WIDTH 1200
# define HEIGTH 600
# define PI 3.141592653589793238462643383279502884197
# define ENEMY_LIVES 3
# define N_TEX 7
# define VIEW_ANGLE 66
# define RAY_ANGLE (VIEW_ANGLE * PI / 180 / WIDTH)


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
	struct s_frame		*frame;
	struct s_ray		*ray;
	struct s_character	*enemy[MAX_ENEMIES + 1];
	mlx_t				*mlx;
	mlx_image_t			*img;
	mlx_image_t			*minimap;
	mlx_texture_t		*tex[N_TEX];
	mlx_texture_t		*enemy_tex;
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
}	t_map;

typedef struct s_frame
{
	unsigned int	counter;
	int	n_backstep;
} t_frame;

void	print_map(t_map *map);

#endif
