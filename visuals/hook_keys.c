/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:14:39 by vlenard           #+#    #+#             */
/*   Updated: 2023/08/30 16:46:18 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/display.h"

void	move_player_vertical(t_map *s, double mv)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_W))
	{
		if (!collide(s->co, (int)(s->px + mv * s->pdx), (int)s->py))
			s->px += mv * s->pdx;
		if (!collide(s->co, (int)(s->px), (s->py + s->pdy * mv)))
			s->py += mv * s->pdy;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_S))
	{
		if (!collide(s->co, (int)(s->px - mv * s->pdx), (int)s->py))
			s->px -= mv * s->pdx;
		if (!collide(s->co, (int)(s->px), (int)(s->py - s->pdy * mv)))
			s->py -= mv * s->pdy;
	}
}

void	move_player_horizontal(t_map *s, double mv)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_A))
	{
		if (!collide(s->co, (int)(s->px + mv * s->pdy), (int)s->py))
			s->px += mv * s->pdy;
		if (!collide(s->co, (int)(s->px), (int)(s->py - mv * s->pdx)))
			s->py -= mv * s->pdx;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_D))
	{
		if (!collide(s->co, (int)(s->px - mv * s->pdy), (int)s->py))
			s->px -= mv * s->pdy;
		if (!collide(s->co, (int)(s->px), (int)(s->py + mv * s->pdx)))
			s->py += mv * s->pdx;
	}
}

void	change_direction_keys(t_map *s, double mv)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_LEFT)
		|| (mlx_is_key_down(s->mlx, MLX_KEY_Q)))
	{
		s->pa -= mv;
		if (s->pa < 0)
			s->pa += 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_RIGHT)
		|| (mlx_is_key_down(s->mlx, MLX_KEY_E)))
	{
		s->pa += mv;
		if (s->pa > 2 * PI)
			s->pa -= 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
}

void	key_bindings(mlx_key_data_t keydata, void *p)
{
	t_map	*s;

	s = (t_map *) p;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(s->mlx);
		full_exit(s);
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_SPACE))
		door_mov(s);
	if (mlx_is_key_down(s->mlx, MLX_KEY_ENTER))
		s->shoot = true;
}

void	check_keys(t_map *s)
{
	move_player_vertical(s, (float) WALKING_SPEED / 100);
	move_player_horizontal(s, (float) SIDEWALK_SPEED / 100);
	change_direction_keys(s, (float) CHANGE_DIRECTION / 100);
	change_direction_mouse(s, (float) CHANGE_DIRECTION / 100);
}
