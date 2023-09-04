/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:42:22 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/04 18:00:59 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/display.h"

int	choose_texture(t_ray *r)
{
	int	wall_side;

	if (r->door_visible == 1)
		return (DOOR_T);
	if (r->hit_side == XSIDE)
	{
		if (r->rdx > 0)
			wall_side = WEST_T;
		else
			wall_side = EAST_T;
	}
	else
	{
		if (r->rdy < 0)
			wall_side = NORTH_T;
		else
			wall_side = SOUTH_T;
	}
	return (wall_side);
}

int	color_tex(t_ray *r, mlx_texture_t *tex, int py, bool mirror_tex)
{
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			tex_step;

	if (!tex)
		perror ("no texture for walls");
	tex_step = 1.0 * tex->height / r->lineheight;
	wall_x = r->hit_x - (int)r->hit_x;
	if ((r->hit_side) == 0)
		wall_x = r->hit_y - (int)r->hit_y;
	if (mirror_tex)
		wall_x = (1 - wall_x);
	tex_x = (int)(wall_x * tex->width);
	tex_y = (py - HEIGTH / 2 + r->lineheight / 2) * tex_step;
	return (tex_color(tex, tex_x, tex_y));
}

void	take_texture(t_map *s, int p1, int p2, int px)
{
	mlx_texture_t	*tex;
	int				start;
	int				end;
	bool			mirror_tex;

	start = p1;
	end = p2;
	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	tex = s->tex[choose_texture(s->ray)];
	mirror_tex = false;
	if (tex == s->tex[SOUTH_T] || tex == s->tex[EAST_T])
		mirror_tex = true;
	while (start < end)
	{
		mlx_put_pixel(s->img, px, start,
			color_tex(s->ray, tex, start, mirror_tex));
		start++;
	}
}

void	draw_ceiling(t_map *s, int p_end, int px)
{
	int	i;

	i = -1;
	if (p_end <= 0)
		return ;
	while (++i <= p_end)
		mlx_put_pixel(s->img, px, i, s->ceiling);
}

void	draw_floor(t_map *s, int p_start, int px)
{
	if (p_start >= HEIGTH)
		return ;
	while (++p_start < HEIGTH)
		mlx_put_pixel(s->img, px, p_start, s->floor);
}
