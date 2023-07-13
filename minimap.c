/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 10:25:30 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/13 14:15:16 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_wall(t_data *s, int x, int y)
{
	int img_size;

	img_size = WIDTH / 25;
	if (s->co[x][y] == '1')
	{
		mlx_image_t *img = mlx_new_image(s->mlx, img_size, img_size);
		memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
		if (mlx_image_to_window(s->mlx, img, x * img_size, y * img_size) < 0)
			full_exit();
	}
	return (0);
}

int	draw_minimap(t_data *s)
{
	scan_coordinates(s, print_wall);
	return (1);
}