#include "../include/cub3d.h"

void	to_vert_line(t_map *s, int p1, int p2, int px, t_character *e)
{
	int	color;
	int	start = p1;
	int	end = p2;

	color = 0xff0000ff;
	if (e->index == 1)
		color = 0xffff00ff;
	if (e->index == 2)
		color = 0xa7c5f9ff;
	// if (p2 < p1)
	// {
	// 	start = p2;
	// 	end = p1;
	// }
	// if (start < 0)
	// 	start = 0;
	// if (end >= HEIGTH)
	// 	end = HEIGTH - 1;
	while (start < end)
	{
		mlx_put_pixel(s->img, px, start, color);
		start++;
	}
}

void	check_enemy(t_map *s, t_ray *r)
{
	int	i;

	i = -1;
	while (s->enemy[++i])
	{
		if ((r->xmap == (int)s->enemy[i]->x) && r->ymap == (int)s->enemy[i]->y)
			s->enemy[i]->visible = true;
	}
} 

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
		//e->ray_start = s->ray->ra;
	}
	else if ((ray_a < e->a_left || ray_a > e->a_right) && e->in_view == true)
	{
		e->in_view = false;
		e->pix_end = s->ray->x_px;
	//e->ray_end = s->ray->ra;
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
	//printf("xpos_tex %f, py %d, tex_y %d, tex_step %d, lineheight %d\n", x_pos, py, tex_y, tex_step, e->lineheight);
	pos = (tex_y * e->tex->width + tex_x) * e->tex->bytes_per_pixel;
	color = to_rgbt(e->tex->pixels[pos + 0], e->tex->pixels[pos + 1],
		e->tex->pixels[pos + 2], e->tex->pixels[pos + 3]);
	//printf ("xpos")
	return (color);

}

void	draw_enemy_tex(t_map *s, int p1, int p2, t_character *e)
{
	if (p1 > p2)
	{
		perror("drawing enemy texture in wrong direction");
		return ;
	}
	while (p1 < p2)
	{
		mlx_put_pixel(s->img, e->px, p1, color_enemy_tex(s, e, p1));
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
