
#include "../include/cub3d.h"

t_ray	*init_ray(t_map *s, t_ray *ray, double angle, int px)
{	
	ray->x_px = px;
	ray->ra = s->pa - angle * WIDTH / 2 + px * angle;
	ray->rdx = cos(ray->ra);
	ray->rdy = sin(ray->ra);
	ray->deltadist_x = delta_dist(ray->rdx);
	ray->deltadist_y = delta_dist(ray->rdy);
	ray->xmap = (int)s->px;
	ray->ymap = (int)s->py;
	ray->hit_side = 0;
	ray->hit_x = 0;
	ray->hit_y = 0;
	ray->lineheight = 0;
	ray->door = 0;
	return (ray);
}

void	draw_stripe(t_map *s, t_ray *r, double dist, int px)
{
	int	drawstart;
	int drawend;

	r->lineheight = HEIGTH / dist;
	drawstart = HEIGTH / 2 - r->lineheight / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = HEIGTH / 2 + r->lineheight / 2;
	if (drawend >= HEIGTH)
		drawend = HEIGTH - 1;
	draw_ceiling(s, drawstart - 1, px);
	take_texture(s, drawstart, drawend, px);
	draw_floor(s, drawend - 1, px);
	
}

void	minimap_perspective(t_map *s, t_ray *ray)
{
	double	x;
	double	y;
	double	pixel_x;
	double	pixel_y;
	int		pixels;

	x = (ray->hit_x - s->px) * s->mm_square;
	y = (ray->hit_y - s->py) * s->mm_square;
	pixels = (sqrt((x * x) + (y * y)));
	x /= pixels;
	y /= pixels;
	pixel_x = s->px * s->mm_square;
	pixel_y = s->py * s->mm_square;
	while (pixels)
	{
		mlx_put_pixel(s->minimap, (int)(pixel_x) , (int)(pixel_y), 0xFF0000FF);
		pixel_x += x;
		pixel_y += y;
		--pixels; 
	}
}

void	raycaster(t_map *s, t_ray *ray)
{
	int	px = 0;
	ray->raylength = 0;
	ray->door_x = -1;
	ray->door_y = -1;
	loop_enemies(s, enemy_invisible);
	memset(s->img->pixels, 255, s->img->width * s->img->height * sizeof(int32_t));
	while (px < WIDTH)
	{
		ray = init_ray(s, ray, RAY_ANGLE, px);
		init_dda(s, ray);
		dda(s, ray, px);
		minimap_perspective(s, ray);
		draw_stripe(s, ray, ray->raylength, px);
		loop_enemies(s, raycast_enemy);
		px++;
	}
	draw_enemies(s);
	//loop_enemies(s, draw_enemy);
}
