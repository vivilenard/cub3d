/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attacks.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:41:35 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/04 18:17:47 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/display.h"

int	attack_player(t_map *s, t_character *e)
{
	if (!e->lives)
		return (1);
	if (e->visible && e->dist < 0.8 && s->lives > 0)
		s->lives--;
	return (1);
}

int	get_shot(t_map *s)
{
	int		lives_tmp;
	float	mv;

	mv = 0.05;
	lives_tmp = s->lives;
	if (s->frame->counter % 50 == 0)
		loop_enemies(s, attack_player);
	if (lives_tmp <= s->lives && !s->frame->n_backstep)
		return (0);
	if (lives_tmp > s->lives)
	{
		if (SOUND)
			system("afplay sounds/Snare.wav&");
		color_full_screen(s->img, 0xFF0000FF);
		s->frame->n_backstep = 10;
		return (1);
	}
	if (!collide(s->co, (int)(s->px - mv * s->pdx), (int)s->py))
		s->px -= mv * s->pdx;
	if (!collide(s->co, (int)(s->px), (int)(s->py - s->pdy * mv)))
		s->py -= mv * s->pdy;
	if (s->frame->n_backstep)
		s->frame->n_backstep--;
	return (0);
}

void	put_texture(t_map *s, mlx_texture_t *tex, int size)
{
	int		x;
	int		y;
	double	tex_step;
	t_color	color;

	tex_step = 1.0 * tex->height / size;
	x = 0;
	while (x < size && size <= WIDTH)
	{
		y = 0;
		while (y < size && size <= HEIGTH)
		{
			color = tex_color(tex, (int)(x * tex_step), (int)(y * tex_step));
			if (color)
				mlx_put_pixel(s->img, x + (WIDTH / 2 - size / 2), y, color);
			y++;
		}
		x++;
	}
}

int	die(t_map *s)
{
	mlx_image_t		*i;
	mlx_texture_t	*tex;

	if (s->lives > 0)
		return (0);
	mlx_delete_image(s->mlx, s->minimap);
	s->gun_img->enabled = false;
	color_full_screen(s->img, 0x00000000);
	tex = mlx_load_png("./textures/sad_smile.png");
	if (!tex)
		return (0);
	i = mlx_texture_to_image(s->mlx, tex);
	mlx_delete_texture(tex);
	mlx_image_to_window(s->mlx, i, WIDTH / 2 - HEIGTH / 2, 0);
	mlx_resize_image(i, HEIGTH, HEIGTH);
	return (1);
}

void	shoot_enemy(t_map *s, t_character *e)
{
	float	shift_x;
	float	shift_y;

	if (e->lives <= 0)
		return ;
	e->lives--;
	shift_x = e->x - e->dx / sqrtf((e->dx * e->dx + e->dy * e->dy)) * 0.2;
	shift_y = e->y - e->dy / sqrtf((e->dx * e->dx + e->dy * e->dy)) * 0.2;
	if (s->co[(int)shift_y][(int)shift_x] != WALL
		&& s->co[(int)shift_y][(int)shift_x] != CLOSED_DOOR)
	{
		e->x = shift_x;
		e->y = shift_y;
	}
}
