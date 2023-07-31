/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 16:43:37 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/31 13:16:54 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	choose_texture(t_data *s)
{
	int	wall_side;
	
	if (s->hit_side == 0) //side x
	{
		if (s->pdx > 0)
			wall_side = 3; //west
		else
			wall_side = 2; //east
	}
	else
	{
		if (s->pdy < 0)
			wall_side = 0;//no
		else
			wall_side = 1;//so
	}
	return (wall_side);
}

int	color_tex(t_data *s, int py)
{
	int				color;
	mlx_texture_t	*tex;
	int				pos;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			tex_step;

	tex = s->tex[choose_texture(s)];
	tex_step = 1.0 * tex->height / s->lineheight;
	if (!tex)
		perror ("no tex");
	wall_x = s->hit_x - (int)s->hit_x;
	if ((s->hit_side) == 0)
		wall_x = s->hit_y - (int)s->hit_y;
	tex_x = (int)(wall_x * tex->width);
	tex_y = (py - HEIGTH / 2 + s->lineheight / 2) * tex_step;
	pos = (tex_y * tex->width + tex_x) * tex->bytes_per_pixel;
	color = to_rgbt(tex->pixels[pos + 0], tex->pixels[pos + 1],
		tex->pixels[pos + 2], tex->pixels[pos + 3]);
	return (color);
}

void	take_texture(t_data *s, int p1, int p2, int px)
{
	int	start;
	int	end;

	start = p1;
	end = p2;
	if (p2 < p1)
	{
		start = p2;
		end = p1;
	}
	while (start < end)
	{
		mlx_put_pixel(s->img, px, start, color_tex(s, start));
		start++;
	}
}
