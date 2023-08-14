#include "../include/cub3d.h"

int	raycast_enemy(t_map *s, t_character *e)
{
	double	ray_a;

	if (e->visible == false)
		return (0);
	ray_a = s->ray->ra;
	if (e->in_view == false && ((ray_a > e->a_left && ray_a < e->a_right)
		|| ((e->a_left > e->a_right) 
		&& ((ray_a < 2 * PI && ray_a >= e->a_left) || (ray_a >= 0 && ray_a <= e->a_right)))))
	{
		e->in_view = true;
		e->pix_start = s->ray->x_px;
	}
	else if (e->in_view == true && ((((e->a_left < e->a_right) && (((ray_a > e->a_right) || ray_a < e->a_left))))
		|| ((e->a_left > e->a_right) && (((ray_a < e->a_left && ray_a > e->a_right))))))
	{
		e->in_view = 2;
		e->pix_end = s->ray->x_px;
	}
	//	printf("ea_l: %f, ra: %f ea_r: %f\n", e->a_left, ray_a, e->a_right);
	return (1);
}

color	color_enemy_tex(t_map *s, t_character *e, int py)
{
	int			tex_x;
	int			tex_y;
	double		tex_step;
	int			pos;
	int			color;
	double		x_pos;
	double		r_a_right;

	//doesnt work between eleft and ea;
	if (!e->tex)
		perror("no enemy texture");
	tex_step = 1.0 * e->tex->height / e->lineheight;
	x_pos = (e->ray_a - e->a_left) / (e->a_right - e->a_left);
	tex_x = (int)(x_pos * e->tex->width); //check where ray angle hits enemy plane
	tex_y = ((py - HEIGTH / 2 + e->lineheight / 2) * tex_step);
	// if (e->ray_a > 29 / 15 * PI && e->ray_a < 44 / 15 * PI)
	// 	printf("ra left: %f, ray: %f, ra right: %f\n", e->a_left, e->ray_a, e->a_right);
	pos = (tex_y * e->tex->width + tex_x) * e->tex->bytes_per_pixel;
	color = to_rgbt(e->tex->pixels[pos + 0], e->tex->pixels[pos + 1],
		e->tex->pixels[pos + 2], e->tex->pixels[pos + 3]);
	return (color);

}

void	draw_enemy_tex(t_map *s, int p1, int p2, t_character *e)
{
	color	tex_color;
	if (p1 > p2)
	{
		perror("drawing enemy texture in wrong direction");
		return ;
	}
	if (p1 < 0)
		p1 = 0;
	if (p2 >= HEIGTH)
		p2 = HEIGTH - 1;
	while (p1 < p2)
	{
		tex_color = color_enemy_tex(s, e, p1);
		if (tex_color > 0)
			mlx_put_pixel(s->img, e->px, p1, tex_color);
		p1++;
	}
}

int	draw_enemy(t_map *s, t_character *e)
{
	int	p1;
	int	p2;

	double pa;
	if ((e->pix_start < 0))
		return (0);
	if (e->pix_end < 0)
		e->pix_end = WIDTH - 1;
	e->px = e->pix_start;
	e->lineheight = HEIGTH / e->dist;
	p1 = HEIGTH / 2 - e->lineheight / 2;
	p2 = HEIGTH / 2 + e->lineheight / 2;
	//printf("drawing\n");
	while (e->px >= 0 && (e->px < e->pix_end && e->px < WIDTH))
	{
		pa = s->pa;
		if (pa - RAY_ANGLE * WIDTH / 2 + e->px * RAY_ANGLE < 0)
			pa += 2 * PI;
		else if (pa - RAY_ANGLE * WIDTH / 2 + e->px * RAY_ANGLE > 2 * PI)
			pa -= 2 * PI;
		e->ray_a = pa - RAY_ANGLE * WIDTH / 2 + e->px * RAY_ANGLE;
		draw_enemy_tex(s, p1, p2, e);
		//to_vert_line(s, p1, p2, e->px, e);
		e->px++;
	}
	return (1);
}

void	draw_enemies(t_map *s)
{
	int		i;
	int		e_index;
	double	dist[MAX_ENEMIES];

	e_index = 0;
	i = -1;
	int n_enemies = number_enemies(s);
	while (s->enemy[++i])
		dist[i] = s->enemy[i]->dist;
	while (1)
	{
		e_index = highest_dist_enemy(s, dist);
		if (e_index < 0)
			break;
		draw_enemy(s, s->enemy[e_index]);
		dist[e_index] = -1;
		//stops drawing at distance 0.6
	}
}