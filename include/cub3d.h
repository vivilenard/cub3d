#ifndef CUB3D_H

# define CUB3D_H

# define WIDTH 1800
# define HEIGTH 1200
# define PI 3.141592653589793238462643383279502884197
# define DR 0.0174533
# define RED_RGBT 0xff3800ff
# define BLUE_RGBT 0xa7c5f9ff
# define GREEN_RGBT 0x9acd32ff
# define YELLOW_RGBT 0xffff00ff

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include "parser.h"
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

typedef struct s_map
{
	struct s_ray	*ray;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	mlx_texture_t	*tex[10];	//space for 10 textures -- dont know how much we need
	char			**co;
	int				map_height;
	int				map_width;
	double			px;			//player position
	double			py;
	double			pa;			//player angle
	double			pdx; 		//player direction vector
	double			pdy;
	double			p_radius;	//size of player in minimap
	int				mm_radius;	//size of minimap
	int				mm_square;	//size of a tile
	int				mouse_pos;
}	t_map;


typedef struct s_ray
{
	double			ra;
	double			rdx;
	double			rdy;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	int				xmove;
	int				ymove;
	int				xmap;
	int				ymap;
	int				hit_side;
	double			hit_x;
	double			hit_y;
	int				lineheight;
}	t_ray;


int		mapwidth(char *map);
int		mapheight(char *map);

//init
t_map	init(t_map *s, char **argv);
int		assign_line(char *line, t_map *s, int y);
int		allocate_map(t_map *s);
int		map_to_koordinate(t_map *s, char *map);
void	print_coordinates(t_map s);
int		map_to_koordinate(t_map *s, char *map);

//utils
void	full_exit();
int		scan_coordinates(t_map *s, int (*f)(t_map *s, int x, int y));
int		to_rgbt(int r, int g, int b, int t);

//display
int		display(t_map *s);

//minimap
int		draw_minimap(t_map *s);
void	print_square(mlx_image_t *img, int x, int y, int radius, uint32_t color);
void	to_square(t_map *s, double x, double y, double p_radius);

//key_bindings
void	move_player_vertical(t_map *s, double step);
void	move_player_horizontal(t_map *s, double step);
void	key_bindings(void *p);

//raycaster
void	raycaster(t_map *s);
void	draw_line(t_map *s, t_ray *r, double dist, int px);
void	to_vert_line(t_map *s, int p1, int p2, int px);
t_ray	*init_ray(t_map *s, double angle, int r);
void	init_dda(t_map *s, t_ray *r);
double	ray_dist(t_map *s, t_ray *r);
double	dda(t_map *s, t_ray *r);
double	delta_dist(double side);

//texture

void	take_texture(t_map *s, int p1, int p2, int px);
int		color_tex(t_map *s, t_ray *r, int py);
int		choose_texture(t_map *s, t_ray *r);

#endif
