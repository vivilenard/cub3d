/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:36:13 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/04 14:45:10 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H

# define DISPLAY_H

# define RED_RGBT 0xff3800ff
# define BLUE_RGBT 0xa7c5f9ff
# define GREEN_RGBT 0x9acd32ff
# define YELLOW_RGBT 0xffff00ff

# include "cub3d.h"

typedef struct s_character
{
	mlx_texture_t	*tex;
	int				index;
	int				lives;
	double			x;
	double			y;
	double			a;
	double			dx;
	double			dy;
	double			radius;
	double			dist;
	bool			visible;
	int				in_view;
	double			a_left;
	double			a_right;
	double			orth_x;
	double			orth_y;
	double			left_x;
	double			left_y;
	double			right_x;
	double			right_y;
	double			pix_start;
	double			pix_end;
	int				px;
	int				lineheight;
	double			ray_a;
	int				tex_iter;
}	t_character;

typedef struct s_ray
{
	double			mv_angle;
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

//attacks
int		attack_player(t_map *s, t_character *e);
int		get_shot(t_map *s);
int		die(t_map *s);
void	shoot_enemy(t_map *s, t_character *e);

//dda
double	ray_dist(t_ray *r);
int		move_side(t_map *s, t_ray *r, int px, int side);
double	dda(t_map *s, t_ray *r, int px);
void	init_dda(t_map *s, t_ray *r);

//display_extras
void	display_extras(t_map *s);
t_color	tex_color(mlx_texture_t *tex, int x, int y);
void	put_texture_heart(t_map *s, mlx_texture_t *tex,
			double x_pos, double y_pos);
void	display_lives(t_map *s);
void	print_cross(t_map *s, float size, int color);

//display
int		display(t_map *s);
int		setup_game(t_map *s);
void	loop_game(void *p);
void	put_texture_gun(t_map *s);
void	play_music(t_map *s);

//door
void	door_inaccessible(t_ray *ray);
void	check_door(t_map *s, t_ray *r, int px);
void	door_mov(t_map *s);

//draw_functions
void	print_square(t_map *s, int x, int y, u_int32_t color);
void	to_red_square(t_map *s, double x, double y, double p_radius);
void	to_square(t_map *s, double x, double y, double p_radius);
void	color_full_screen(mlx_image_t *img, uint32_t color);
void	put_texture(t_map *s, mlx_texture_t *tex, int size);

//draw_minimap
int		print_wall(t_map *s, int x, int y);
void	draw_player(t_map	*s);
void	draw_view(t_map *s);
int		draw_mini_enemy(t_map *s, t_character *e);
void	minimap_perspective(t_map *s, t_ray *ray);

//help_functions
int		collide(t_map_char **co, int x, int y);
void	frame_count(t_frame *frames);
int		scan_coordinates(t_map *s, int (*f)(t_map *s, int x, int y));

//hook_keys
void	move_player_vertical(t_map *s, double mv);
void	move_player_horizontal(t_map *s, double mv);
void	change_direction_keys(t_map *s, double mv);
void	key_bindings(mlx_key_data_t keydata, void *p);
void	check_keys(t_map *s);

//hook_mouse
void	adjust_view(t_map *s, int x, double mv);
void	change_direction_mouse(t_map *s, double mv);
void	mouse_bindings(mouse_key_t button, action_t action,
			modifier_key_t mods, void *p);

//math
double	delta_dist(double side);
int		calculate_lineheight(double distance);
t_color	to_rgbt(int r, int g, int b, int t);

//minimap
void	calculate_proportions(t_map *s);
int		draw_minimap(t_map *s);
int		setup_minimap(t_map *s);

//raycaster
t_ray	*init_ray(t_map *s, t_ray *ray, double angle, int px);
void	draw_stripe(t_map *s, t_ray *r, double dist, int px);
void	raycaster(t_map *s, t_ray *ray);

//texture
int		choose_texture(t_ray *r);
int		color_tex(t_ray *r, mlx_texture_t *tex, int py);
void	take_texture(t_map *s, int p1, int p2, int px);
void	draw_ceiling(t_map *s, int p_end, int px);
void	draw_floor(t_map *s, int p_start, int px);

//ENEMIES
//calibrate_enemies
void	enemy_angles(t_map *s, t_character *e);
void	enemy_borderpoints(t_character *e);
void	enemy_change_texture(t_map *s, t_character *e);
int		calibrate_enemy(t_map *s, t_character *e);

//draw_enemies
t_color	color_enemy_tex(t_character *e, int py);
void	draw_enemy_tex(t_map *s, int p1, int p2, t_character *e);
int		draw_enemy(t_map *s, t_character *e, double ray_angle);
void	draw_enemies(t_map *s);

//enemy_utils
void	loop_enemies(t_map *s, int (*f)(t_map *s, t_character *e));
bool	continue_walk(t_map_char **co, int x, int y);
void	check_enemy(t_map *s, t_ray *r);
double	angle_of_vector(double xv, double yv);
int		highest_dist_enemy(t_map *s, double *dist);

//init_enemies
void	set_enemy_data(t_map *s, int i, int x, int y);
int		position_enemy(t_map *s, int x, int y);
void	get_enemies(t_map *s);
int		enemy_invisible(t_character *e);

//enemy_view
int		raycast_enemy(t_map *s, t_character *e);
bool	enemy_start_in_view(t_character *e, double ray_a);
bool	enemy_stop_in_view(t_character *e, double ray_a);
#endif
