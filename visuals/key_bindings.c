/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:14:39 by vlenard           #+#    #+#             */
/*   Updated: 2023/08/01 13:53:08 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player_vertical(t_map *s, double mv)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_W))
	{
		if (s->co[(int)(s->px + mv * s->pdx)][(int)s->py] != '1')
			s->px += mv * s->pdx;
		if (s->co[(int)(s->px)][(int)(s->py + s->pdy * mv)] != '1')
			s->py += mv * s->pdy;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_S))
	{
		if (s->co[(int)(s->px - mv * s->pdx)][(int)s->py] != '1')
			s->px -= mv * s->pdx;
		if (s->co[(int)(s->px)][(int)(s->py - s->pdy * mv)] != '1')
			s->py -= mv * s->pdy;
	}
}

void	move_player_horizontal(t_map *s, double mv)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_A))
	{
		if (s->co[(int)(s->px + mv * s->pdy)][(int)s->py] != '1')
			s->px += mv * s->pdy;
		if (s->co[(int)(s->px)][(int)(s->py - mv * s->pdx)] != '1')
			s->py -= mv * s->pdx;
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_D))
	{
		if (s->co[(int)(s->px - mv * s->pdy)][(int)s->py] != '1')
			s->px -= mv * s->pdy;
		if (s->co[(int)(s->px)][(int)(s->py + mv * s->pdx)] != '1')
			s->py += mv * s->pdx;
	}
}

void	change_direction_keys(t_map *s, double mv)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_LEFT) || (mlx_is_key_down(s->mlx, MLX_KEY_Q)))
	{
		s->pa -= mv;
		if (s->pa < 0)
			s->pa += 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_RIGHT) || (mlx_is_key_down(s->mlx, MLX_KEY_E)))
	{
		s->pa += mv;
		if (s->pa > 2 * PI)
			s->pa -= 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
}

void	adjust_view(t_map *s, int x, double mv)
{
	if ( x - s->mouse_pos < 0 && x >= 0 )
	{
		s->pa -= mv;
		if (s->pa < 0)
			s->pa += 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
	else if ( x - s->mouse_pos > 0 && x <= WIDTH )
	{
		s->pa += mv;
		if (s->pa > 2 * PI)
			s->pa -= 2 * PI;
		s->pdx = cos(s->pa);
		s->pdy = sin(s->pa);
	}
}

void	change_direction_mouse(t_map *s, double mv)
{
	int	x;
	int	y;

	x = 0;
	y = 0;

	mlx_get_mouse_pos(s->mlx, &x, &y);
	adjust_view(s, x, mv);
	if (s->mouse_pos >= WIDTH)
		s->mouse_pos = WIDTH / 2;
	else
		s->mouse_pos = x;
}

void	key_bindings(void *p)
{
	t_map *s;

	s = (t_map *) p;
	if (mlx_is_key_down(s->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(s->mlx);
		exit(EXIT_SUCCESS);
	}
	move_player_vertical(s, 0.08);
	move_player_horizontal(s, 0.05);
	change_direction_keys(s, 0.10);
	change_direction_mouse(s, 0.08);
	draw_minimap(s);
	raycaster(s);
}
