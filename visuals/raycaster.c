
#include "../include/cub3d.h"

void	to_vert_line(t_map *s, int p1, int p2, int px)
{
	int	color;
	int	start = p1;
	int	end = p2;

	color = 0xffff00ff;
	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	while (start < end)
	{
		color = 0xff0000ff;
		mlx_put_pixel(s->img, px, start, color);
		start++;
	}
}

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

int	draw_enemy(t_map *s, t_character *e)
{
	if (!(e->pix_start && e->pix_end))
		return (0);
	int px = e->pix_start;
	int	lineheight = HEIGTH / e->dist;
	int p1 = HEIGTH / 2 - lineheight / 2;
	int p2 = HEIGTH / 2 + lineheight / 2;
	while (px <= e->pix_end)
	{
		to_vert_line(s, p1, p2, px);
		px++;
	}
	return (1);
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
	printf("pix1: %f, pix2: %f\n", s->enemy[2]->pix_start, s->enemy[2]->pix_start);
	loop_enemies(s, draw_enemy);
}





	//print details
	// printf("pdx %f/%f\n", s->rdx, s->rdy);	
	// printf("map %d/%d\n", s->xmap, s->ymap);
	// printf("player %f/%f\n", s->px, s->py);
	// printf("move %d/%d\n", s->xmove, s->ymove);
	//printf("deltadist %f/%f\n", delta_dist(s->rdx), delta_dist(s->rdy));
	//printf("sidedist %f/%f\n", s->sidedist_x, s->sidedist_y);