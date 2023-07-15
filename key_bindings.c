/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:14:39 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/15 12:05:20 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_data *s)
{
	double step;

	step = 0.2;
	if (mlx_is_key_down(s->mlx, MLX_KEY_W))
	{
		if (s->py - (step + s->p_radius) < 0)
			return ;
		s->py -= step;
		draw_minimap(s);
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_A))
	{
		if (s->px - (step + s->p_radius) < 0)
			return ;
		s->px -= step;
		draw_minimap(s);
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_S))
	{
		if (s->py + (step + s->p_radius) > s->map_height)
			return ;	
		s->py += step;
		draw_minimap(s);
	}
	if (mlx_is_key_down(s->mlx, MLX_KEY_D))
	{
		if (s->px + (step + s->p_radius) > s->map_width)
			return ;
		s->px += step;
		draw_minimap(s);
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
	move_player(s);
}