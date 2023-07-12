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
	int	**cs;
}	t_data;

# endif
