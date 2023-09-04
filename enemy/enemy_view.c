/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_enemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:57:09 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/04 14:57:40 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/display.h"

bool	enemy_start_in_view(t_character *e, double ray_a)
{
	if (e->in_view == false
		&& ((ray_a > e->a_left && ray_a < e->a_right)
			|| ((e->a_left > e->a_right)
				&& ((ray_a < 2 * PI && ray_a >= e->a_left)
					|| (ray_a > 0 && ray_a <= e->a_right)))))
		return (true);
	return (false);
}

bool	enemy_stop_in_view(t_character *e, double ray_a)
{
	if (e->in_view == true && (((e->a_left < e->a_right
					&& ((ray_a > e->a_right || ray_a < e->a_left))))
			|| (e->a_left > e->a_right
				&& (((ray_a < e->a_left && ray_a > e->a_right))))))
		return (true);
	return (false);
}

int	raycast_enemy(t_map *s, t_character *e)
{
	double	ray_a;

	if (e->visible == false || !e->lives)
		return (0);
	ray_a = s->ray->ra;
	if (ray_a < e->a_right - 2 * PI)
		ray_a += 2 * PI;
	if (enemy_start_in_view(e, ray_a))
	{
		e->in_view = true;
		e->pix_start = s->ray->x_px;
	}
	else if (enemy_stop_in_view(e, ray_a))
	{
		e->in_view = 2;
		e->pix_end = s->ray->x_px;
	}
	if (s->ray->x_px == WIDTH / 2 && e->in_view == 1 && s->shoot == true)
		shoot_enemy(s, e);
	return (1);
}
