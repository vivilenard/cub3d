/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:41:19 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/04 18:23:12 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/display.h"

void	play_music(void)
{
	system("afplay ./sounds/Enlightened_Mind.wav &");
}

int	display(t_map *s)
{
	if (setup_game(s))
		full_exit(s);
	mlx_key_hook(s->mlx, key_bindings, s);
	mlx_mouse_hook(s->mlx, mouse_bindings, s);
	if (BACKGROUND_MUSIC)
		play_music();
	mlx_loop_hook(s->mlx, loop_game, s);
	mlx_loop(s->mlx);
	return (0);
}

int	setup_game(t_map *s)
{
	s->ray = malloc(sizeof(t_ray));
	s->img = mlx_new_image(s->mlx, WIDTH, HEIGTH);
	if (!s->img)
		return (1);
	if (mlx_image_to_window(s->mlx, s->img, 0, 0) < 0)
		return (2);
	get_enemies(s);
	if (!setup_minimap(s))
		return (3);
	put_texture_gun(s);
	mlx_set_cursor_mode(s->mlx, MLX_MOUSE_HIDDEN);
	return (0);
}

void	loop_game(void *p)
{
	t_map	*s;

	s = (t_map *) p;
	if (die(s))
		return ;
	check_keys(s);
	loop_enemies(s, calibrate_enemy);
	draw_minimap(s);
	raycaster(s, s->ray);
	display_extras(s);
	frame_count(s->frame);
	s->shoot = false;
}
