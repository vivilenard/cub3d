/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:53:23 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/15 17:52:15 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	init_player_view(char p)
{
	printf ("VIEW %c\n", p);
	if (p == 'N')
		return (PI * 3 / 2);
	if (p == 'E')
		return (2 * PI);
	if (p == 'S')
		return (PI / 2);
	if (p == 'W')
		return (PI);
	return (0);
}

int	set_player(t_data *s, int x, int y)
{
	printf("set player here: %d/%d\n", x, y);
	s->px = (double)x + 0.5;
	s->py = (double)y + 0.5;
	s->pa = init_player_view(s->co[x][y]);
	printf ("angle %f\n", s->pa);
	s->pdx = cos(s->pa);
	s->pdy = sin(s->pa);
	s->p_radius = 0.09;
	return (1);
}

int	player_position(t_data *s, int x, int y)
{
	if (ft_isalpha(s->co[x][y]))
		return (set_player(s, x, y), 1);
	return (0);
}

t_data	init(t_data *s, char **argv)
{
	s = malloc(sizeof(t_data));
	s->mlx = mlx_init(WIDTH, HEIGTH, "cub3d", false);
	mlx_image_t *img;
	img = mlx_new_image(s->mlx, WIDTH, HEIGTH);
	memset(img->pixels, 0, img->width * img->height * sizeof(int32_t));
	if (mlx_image_to_window(s->mlx, img, 0, 0) < 0)
		full_exit();
	map_to_koordinate(s, argv[1]);
	scan_coordinates(s, player_position);
	//printf ("%d, %d\n", s->map_height, s->map_width);
	return (*s);
}









