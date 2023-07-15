/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:14:39 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/15 17:17:02 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *s, double step)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_W))
	{
		if (s->py - (step + s->p_radius) >= 0 && s->co[(int)s->px][(int)(s->py - step)] != '1')
			s->py -= step;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_A))
	{
		if (s->px - (step + s->p_radius) >= 0 && s->co[(int)(s->px - step)][(int)(s->py)] != '1')
			s->px -= step;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_S))
	{
		if (s->py + (step + s->p_radius) < s->map_height && s->co[(int)s->px][(int)(s->py + step)] != '1')
			s->py += step;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_D))
	{
		if (s->px + (step + s->p_radius) < s->map_width && s->co[(int)(s->px + step)][(int)(s->py)] != '1')
			s->px += step;
	}
	draw_minimap(s);
}

void	change_direction(t_data *s)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_LEFT))
	{
		s->pa -= 0.1;
		if (s->pa < 0)
			s->pa += 2 * PI;
		s->pdx = cos(s->pa);	//cos
		s->pdy = sin(s->pa);	//sin
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_RIGHT))
	{
		s->pa += 0.2;
		if (s->pa > 2 * PI)
			s->pa -= 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
}

void	key_bindings(void *p)
{
	t_data *s;

	s = (t_data *) p;
	if (mlx_is_key_down(s->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(s->mlx);
		exit(EXIT_SUCCESS);
	}
	move_player(s, 0.2);
	change_direction(s);
}