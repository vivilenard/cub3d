#ifndef CUB3D_H

# define CUB3D_H

# define WIDTH 1200
# define HEIGTH 800
# define PI 3.141592653589793238462643383279502884197
# define DR 0.0174533
# define RED_RGBT 0xff3800ff
# define BLUE_RGBT 0xa7c5f9ff
# define GREEN_RGBT 0x9acd32ff
# define YELLOW_RGBT 0xffff00ff

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include "MLX42/include/MLX42/MLX42.h"
#include "libft/libft.h"

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	int				mm_radius;
	int				mm_square;
	mlx_texture_t	*txt;
	char			**co;
	int				map_height;
	int 			map_width;
	double			px;
	double			py;
	double			pa;
	double			pdx;
	double			pdy;
	double			p_radius;
	double			ra;
	double			rdx;
	double			rdy;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;	int				xmove;
	int				ymove;
	int				xmap;
	int				ymap;
	int				hit_side;
}	t_data;

int		mapwidth(char *map);
int		mapheight(char *map);

//init
t_data	init(t_data *s, char **argv);
int		assign_line(char *line, t_data *s, int	y);
int		allocate_map(t_data *s);
int		map_to_koordinate(t_data *s, char *map);
void	print_coordinates(t_data s);
int		map_to_koordinate(t_data *s, char *map);

//utils
void	full_exit();
int		scan_coordinates(t_data *s, int (*f)(t_data *s, int x, int y));
int		ft_torgbt(int r, int g, int b, int t);


//minimap
int		draw_minimap(t_data *s);
void	 print_square(mlx_image_t *img, int x, int y, int radius, uint32_t color);
void	to_square(t_data *s, double x, double y, double p_radius);

//parser
int		parser(int argc);

//key_bindings
void	move_player(t_data *s, double step);
void	key_bindings(void *p);

//raycaster
void	raycaster(t_data *s);
void	draw_line(t_data *s, double dist, int px);
void	to_vert_line(t_data *s, int p1, int p2, int px);
void	init_ray(t_data *s, double angle, int r);
void	init_dda(t_data *s);
double	ray_dist(t_data *s);
double	dda(t_data *s);
double	delta_dist(double side);



# endif
