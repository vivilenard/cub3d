#ifndef CUB3D_H

# define CUB3D_H


// # define RED_RGBT 0xff3800ff
// # define BLUE_RGBT 0xa7c5f9ff
// # define GREEN_RGBT 0x9acd32ff
// # define YELLOW_RGBT 0xffff00ff

# include "main.h"


typedef struct s_character
{
	mlx_texture_t *tex;
	int		index;
	int		lives;
	double	x;
	double	y;
	double	a;
	double	dx;
	double	dy;
	double	radius;
	double	dist;
	bool	visible;
	int		in_view;
	double	a_left;
	double	a_right;
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
	//double	ray_start; //dont need
	//double	ray_end;	//dont need
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
	int				door_visible;
	double			raylength;
	int				door_x;
	int				door_y;
}	t_ray;

//utils
void	full_exit();
int		scan_coordinates(t_map *s, int (*f)(t_map *s, int x, int y));
int		to_rgbt(int r, int g, int b, int t);

//display
int		display(t_map *s);
void	loop_game(void *p);
int		setup_game(t_map *s);

//minimap
int		setup_minimap(t_map *s);
int		draw_minimap(t_map *s);
void	print_square(mlx_image_t *img, int x, int y, int radius, uint32_t color);
void	to_square(t_map *s, double x, double y, double p_radius);
void	to_red_square(t_map *s, double x, double y, double p_radius);


//key_bindings
void	check_keys(t_map *s);
void	move_player_vertical(t_map *s, double step);
void	move_player_horizontal(t_map *s, double step);
void	change_direction_mouse(t_map *s, double mv);
void	change_direction_keys(t_map *s, double mv);
void	adjust_view(t_map *s, int x, double mv);
int		collide(t_map_char **co, int x, int y);
void	key_bindings(mlx_key_data_t keydata, void *p);
void	mouse_bindings(mouse_key_t button, action_t action, modifier_key_t mods, void *p);

//raycaster
void	raycaster(t_map *s, t_ray *ray);
void	draw_line(t_map *s, t_ray *r, double dist, int px);
t_ray	*init_ray(t_map *s, t_ray *ray, double angle, int r);
void	init_dda(t_map *s, t_ray *r);
double	ray_dist(t_ray *r);
double	dda(t_map *s, t_ray *r, int px);
double	delta_dist(double side);
void	check_door(t_map *s, t_ray *r, int px);

//texture

void	take_texture(t_map *s, int p1, int p2, int px);
int		color_tex(t_map *s, t_ray *r, int py);
int		choose_texture(t_ray *r);
void	draw_ceiling(t_map *s, int p_end, int px);
void	draw_floor(t_map *s, int p_start, int px);

//enemies
t_character	*create_enemy();
int			position_enemy(t_map *s, int x, int y);
void		get_enemies(t_map *s);
void		loop_enemies(t_map *s, int (*f)(t_map *s, t_character *e));
int			calibrate_enemy(t_map *s, t_character *e);
int			draw_mini_enemy(t_map *s, t_character *e);
int			raycast_enemy(t_map *s, t_character *e);
void		draw_enemies(t_map *s);
int			draw_enemy(t_map *s, t_character *e);
int			enemy_invisible(t_character *e);
void		check_enemy(t_map *s, t_ray *r);
void		to_vert_line(t_map *s, int p1, int p2, int px, t_character *e);
int			number_enemies(t_map *s);
int			highest_dist_enemy(t_map *s, double *dist);
void		shoot_enemy(t_map *s, t_character *e);

//utils
void		frame_count(t_map *s);
void		color_full_screen(mlx_image_t *img, uint32_t color);

//attacks
int			get_shot(t_map *s);
int			attack_player(t_map *s, t_character *e);
int 		die(t_map *s);


#endif
