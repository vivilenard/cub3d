/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:14:39 by vlenard           #+#    #+#             */
/*   Updated: 2023/08/07 10:29:27 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int		collide(char c)
// {
// 	if (c == WALL || c == CLOSED_DOOR)
// 		return (1);
// 	return (0);
// }
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

void	door_mov(t_map *s)
{
	if (mlx_is_key_down(s->mlx, MLX_KEY_SPACE))
	{
		if (s->ray->door_x < 0 && s->ray->door_y < 0)
			return ;
		if (s->co[s->ray->door_x][s->ray->door_y] == CLOSED_DOOR)
			s->co[s->ray->door_x][s->ray->door_y] = SPACE;
		
	}
}

void	key_bindings(void *p)
{
	t_map *s;

	s = (t_map *) p;
	if (mlx_is_key_down(s->mlx, MLX_KEY_ESCAPE))
	{
		mlx_terminate(s->mlx);
		full_exit(s);
	}
	mlx_set_cursor_mode(s->mlx, MLX_MOUSE_HIDDEN);
	move_player_vertical(s, 0.08);
	move_player_horizontal(s, 0.05);
	change_direction_keys(s, 0.10);
	change_direction_mouse(s, 0.06);
	door_mov(s);
	loop_enemies(s, calibrate_enemy);
	draw_minimap(s);
	raycaster(s, s->ray);
	//move_enemies(s, s->ray);
}
