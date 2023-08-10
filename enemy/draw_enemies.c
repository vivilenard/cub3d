#include "../include/cub3d.h"

int	raycast_enemy(t_map *s, t_character *e)
{
	if (e->visible == false)
		return (0);
	double	ray_a;

	ray_a = s->ray->ra;
	if (((ray_a > e->a_left && !(ray_a > e->a_right))
		|| (!(ray_a < e->a_left) && (ray_a < e->a_right)))
			&& e->in_view == false)
	{
		e->in_view = true;
		e->pix_start = s->ray->x_px;
	}
	else if ((ray_a < e->a_left || ray_a > e->a_right) && e->in_view == true)
	{
		e->in_view = false;
		e->pix_end = s->ray->x_px;
	}
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

	if (!e->tex)
		perror("no enemy texture");
	tex_step = 1.0 * e->tex->height / e->lineheight;
	x_pos = (e->ray_a - e->a_left) / (e->a_right - e->a_left);
	tex_x = (int)(x_pos * e->tex->width); //check where ray angle hits enemy plane
	tex_y = ((py - HEIGTH / 2 + e->lineheight / 2) * tex_step);
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

	if ((!e->pix_start)) //!pixend
		return (0);
	e->lineheight = HEIGTH / e->dist;
	p1 = HEIGTH / 2 - e->lineheight / 2;
	p2 = HEIGTH / 2 + e->lineheight / 2;
	e->px = e->pix_start;
	while (e->px && (e->px < e->pix_end && e->px < WIDTH))
	{
		e->ray_a = s->pa - RAY_ANGLE * WIDTH / 2 + e->px * RAY_ANGLE;
		draw_enemy_tex(s, p1, p2, e);
		//to_vert_line(s, p1, p2, e->px, e);
		e->px++;
	}
	return (1);
}

void	draw_enemies(t_map *s)
{
	int	i;
	int	e_index;
	int	dist[MAX_ENEMIES];

	e_index = 0;
	i = -1;
	while (s->enemy[++i])
		dist[i] = s->enemy[i]->dist;
	while (1)
	{
		e_index = highest_dist_enemy(s, dist);
		if (e_index < 0)
			break;
		draw_enemy(s, s->enemy[e_index]);
		dist[e_index] = 0;
	}
}
