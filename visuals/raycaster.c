
#include "../include/cub3d.h"

t_ray	*init_ray(t_map *s, t_ray *ray, double angle, int r)
{	
	ray->ra = s->pa - angle * WIDTH / 2 + r * angle;
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
	take_texture(s, drawstart, drawend, px);
	
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
	//to_square(s, ray->hit_x, ray->hit_y, 0.05);
}

void	raycaster(t_map *s, t_ray *ray)
{

	double angle;

	angle = 1.15 / WIDTH;  //1.15 ~ 66 degree
	int	px = 0;
	
	memset(s->img->pixels, 255, s->img->width * s->img->height * sizeof(int32_t));
	while (px < WIDTH)
	{
		ray = init_ray(s, ray, angle, px);
		init_dda(s, ray);
		dda(s, ray);
		minimap_perspective(s, ray);
		draw_stripe(s, ray, ray_dist(s, ray) * cos(s->pa - ray->ra) , px);
		px++;
	}
}





	//print details
	// printf("pdx %f/%f\n", s->rdx, s->rdy);	
	// printf("map %d/%d\n", s->xmap, s->ymap);
	// printf("player %f/%f\n", s->px, s->py);
	// printf("move %d/%d\n", s->xmove, s->ymove);
	//printf("deltadist %f/%f\n", delta_dist(s->rdx), delta_dist(s->rdy));
	//printf("sidedist %f/%f\n", s->sidedist_x, s->sidedist_y);