/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:14:39 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/31 13:16:37 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_player(t_data *s, double mv)
{
	//simple_steps(s, step);
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
	move_player(s, 0.1);
	change_direction(s);
	draw_minimap(s);
	raycaster(s);
}