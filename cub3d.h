#ifndef CUB3D_H

# define CUB3D_H

# define WIDTH 800
# define HEIGTH 800

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"
//#include "libft/get_next_line/get_next_line.h"

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*txt;
	char	**co;
	int	map_height;
	int map_width;
}	t_data;

int		mapwidth(char *map);
int		mapheight(char *map);
int		assign_line(char *line, t_data *s, int	y);
t_data	init(t_data *s, char **argv);
int		allocate_map(t_data *s);
int	map_to_koordinate(t_data *s, char *map);

# endif
