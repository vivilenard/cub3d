/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:56:14 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/04 14:56:52 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/display.h"

t_color	color_enemy_tex(t_character *e, int py)
{
	int			tex_x;
	int			tex_y;
	double		tex_step;
	int			pos;
	double		x_pos;

	if (e->ray_a < e->a_right - 2 * PI)
		e->ray_a += 2 * PI;
	if (!e->tex)
		perror("no enemy texture");
	tex_step = 1.0 * e->tex->height / e->lineheight;
	x_pos = (e->ray_a - e->a_left) / (e->a_right - e->a_left);
	tex_x = e->tex_iter * (e->tex->width / E_TEX_ITER)
		+ (int)(x_pos * (e->tex->width / E_TEX_ITER));
	tex_y = ((py - HEIGTH / 2 + e->lineheight / 2) * tex_step);
	pos = ((tex_y * e->tex->width + tex_x) * e->tex->bytes_per_pixel);
	return (to_rgbt(e->tex->pixels[pos + 0], e->tex->pixels[pos + 1],
			e->tex->pixels[pos + 2], e->tex->pixels[pos + 3]));
}

void	draw_enemy_tex(t_map *s, int p1, int p2, t_character *e)
{
	t_color	tex_color;

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
		tex_color = color_enemy_tex(e, p1);
		if (tex_color > 0)
			mlx_put_pixel(s->img, e->px, p1, tex_color);
		p1++;
	}
}

int	draw_enemy(t_map *s, t_character *e, double ray_angle)
{
	int		p1;
	int		p2;
	double	pa;

	if ((e->pix_start < 0))
		return (0);
	if (e->pix_end < 0)
		e->pix_end = WIDTH - 1;
	e->px = e->pix_start;
	e->lineheight = calculate_lineheight(e->dist) * ENEMY_HEIGHT;
	p1 = HEIGTH / 2 - e->lineheight / 2;
	p2 = HEIGTH / 2 + e->lineheight / 2;
	while (e->px >= 0 && (e->px < e->pix_end && e->px < WIDTH))
	{
		pa = s->pa;
		if (s->pa - ray_angle * WIDTH / 2 + e->px * ray_angle <= 0)
			pa += 2 * PI;
		else if (s->pa - ray_angle * WIDTH / 2 + e->px * ray_angle > 2 * PI)
			pa -= 2 * PI;
		e->ray_a = pa - ray_angle * WIDTH / 2 + e->px * ray_angle;
		draw_enemy_tex(s, p1, p2, e);
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
	if (!s->enemy[0])
		return ;
	while (s->enemy[++i])
		dist[i] = s->enemy[i]->dist;
	while (1)
	{
		e_index = highest_dist_enemy(s, dist);
		if (e_index < 0)
			break ;
		if (s->enemy[e_index]->lives > 0)
			draw_enemy(s, s->enemy[e_index], s->ray->mv_angle);
		dist[e_index] = -1;
	}
}
