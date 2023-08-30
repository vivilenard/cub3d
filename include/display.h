#ifndef DISPLAY_H

# define DISPLAY_H


# define RED_RGBT 0xff3800ff
# define BLUE_RGBT 0xa7c5f9ff
# define GREEN_RGBT 0x9acd32ff
# define YELLOW_RGBT 0xffff00ff

# include "cub3d.h"

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
	int		tex_iter;
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

typedef enum e_wallside
{
	XSIDE,
	YSIDE,
}	t_wallside;

//utils
void		full_exit();
int			scan_coordinates(t_map *s, int (*f)(t_map *s, int x, int y));
color		to_rgbt(int r, int g, int b, int t);
void		print_cross(t_map *s, float size, int color);
void		door_mov(t_map *s);

//display
int			display(t_map *s);
void		loop_game(void *p);
int			setup_game(t_map *s);

//minimap
int			setup_minimap(t_map *s);
int			draw_minimap(t_map *s);
void		print_square(t_map *s, int x, int y, uint32_t color);
void		to_square(t_map *s, double x, double y, double p_radius);
void		to_red_square(t_map *s, double x, double y, double p_radius);


//key_bindings
void		check_keys(t_map *s);
void		move_player_vertical(t_map *s, double step);
void		move_player_horizontal(t_map *s, double step);
void		change_direction_mouse(t_map *s, double mv);
void		change_direction_keys(t_map *s, double mv);
void		adjust_view(t_map *s, int x, double mv);
int			collide(t_map_char **co, int x, int y);
void		key_bindings(mlx_key_data_t keydata, void *p);
void		mouse_bindings(mouse_key_t button, action_t action, modifier_key_t mods, void *p);

//raycaster
void		raycaster(t_map *s, t_ray *ray);
void		draw_line(t_map *s, t_ray *r, double dist, int px);
t_ray		*init_ray(t_map *s, t_ray *ray, double angle, int r);
void		init_dda(t_map *s, t_ray *r);
double		ray_dist(t_ray *r);
double		dda(t_map *s, t_ray *r, int px);
double		delta_dist(double side);
void		check_door(t_map *s, t_ray *r, int px);
int			calculate_lineheight(double distance);

//texture

void		take_texture(t_map *s, int p1, int p2, int px);
int			color_tex(t_ray *r, mlx_texture_t *tex, int py);
int			choose_texture(t_ray *r);
void		draw_ceiling(t_map *s, int p_end, int px);
void		draw_floor(t_map *s, int p_start, int px);

//enemies
t_character	*create_enemy();
int			position_enemy(t_map *s, int x, int y);
bool		continue_walk(t_map_char **co, int x, int y);
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
double		angle_of_vector(double xv, double yv);

//utils
void		frame_count(t_frame *frames);
void		color_full_screen(mlx_image_t *img, uint32_t color);

//attacks
int			get_shot(t_map *s);
int			attack_player(t_map *s, t_character *e);
int 		die(t_map *s);

//display_extras
void		display_extras(t_map *s);
color		tex_color(mlx_texture_t *tex, int x, int y);
void		put_texture(t_map *s, mlx_texture_t *tex, double x_pos, double y_pos);
void		display_lives(t_map *s);
void		minimap_perspective(t_map *s, t_ray *ray);
int			print_wall(t_map *s, int x, int y);
void		draw_player(t_map	*s);
void		door_inaccessible(t_ray *ray);


#endif
