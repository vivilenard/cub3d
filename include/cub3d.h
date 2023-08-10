#ifndef CUB3D_H

# define CUB3D_H

# define WIDTH 1400
# define HEIGTH 800
# define PI 3.141592653589793238462643383279502884197
# define N_ENEMIES 6
# define N_TEX 7
# define VIEW_ANGLE 1.15 //=66 degree
# define RAY_ANGLE (VIEW_ANGLE / WIDTH)
// # define RED_RGBT 0xff3800ff
// # define BLUE_RGBT 0xa7c5f9ff
// # define GREEN_RGBT 0x9acd32ff
// # define YELLOW_RGBT 0xffff00ff

# include "main.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <string.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

typedef struct s_character
{
	mlx_texture_t *tex;
	int		index;
	double	x;
	double	y;
	double	a;
	double	a_left;
	double	a_right;
	double	dx;
	double	dy;
	double	radius;
	double	dist;
	bool	visible;
	bool	in_view;
	double	orth_x;
	double	orth_y;
	double	left_x;
	double	left_y;
	double	right_x;
	double	right_y;
	double	pix_start;
	double	pix_end;
	int		px;
	int		lineheight;
	double	ray_a;
	double	ray_start;
	double	ray_end;
} t_character;

typedef struct s_ray
{
	int				x_px;
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
	int				door;
	double			raylength;
	int				door_x;
	int				door_y;
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
void	minimap(t_map *s);
int		draw_minimap(t_map *s);
void	print_square(mlx_image_t *img, int x, int y, int radius, uint32_t color);
void	to_square(t_map *s, double x, double y, double p_radius);

//key_bindings
void	move_player_vertical(t_map *s, double step);
void	move_player_horizontal(t_map *s, double step);
void	key_bindings(void *p);
void	change_direction_mouse(t_map *s, double mv);
void	adjust_view(t_map *s, int x, double mv);

//raycaster
void	raycaster(t_map *s, t_ray *ray);
void	draw_line(t_map *s, t_ray *r, double dist, int px);
t_ray	*init_ray(t_map *s, t_ray *ray, double angle, int r);
void	init_dda(t_map *s, t_ray *r);
double	ray_dist(t_map *s, t_ray *r);
double	dda(t_map *s, t_ray *r, int px);
double	delta_dist(double side);

//texture

void	take_texture(t_map *s, int p1, int p2, int px);
int		color_tex(t_map *s, t_ray *r, int py);
int		choose_texture(t_map *s, t_ray *r);
void	draw_ceiling(t_map *s, int p_end, int px);
void	draw_floor(t_map *s, int p_start, int px);

//enemies
t_character	*create_enemy(t_map *s, int n);
int			position_enemy(t_map *s, int x, int y);
void		get_enemies(t_map *s);
void		loop_enemies(t_map *s, int (*f)(t_map *s, t_character *e));
int			calibrate_enemy(t_map *s, t_character *e);
int			draw_mini_enemy(t_map *s, t_character *e);
int			raycast_enemy(t_map *s, t_character *e);
void		draw_enemies(t_map *s);
int			draw_enemy(t_map *s, t_character *e);
int			enemy_invisible(t_map *s, t_character *e);
void		check_enemy(t_map *s, t_ray *r);
void		to_vert_line(t_map *s, int p1, int p2, int px, t_character *e);
int			number_enemies(t_map *s);
int			highest_dist_enemy(t_map *s, int *dist);


#endif
