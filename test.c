/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 13:54:58 by vlenard           #+#    #+#             */
/*   Updated: 2023/07/06 11:02:54 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <memory.h>

void	display_sth(void *i)
{
	mlx_image_t *img;
	img = (mlx_image_t *) i;
	img->instances[0].x += 5;
	img->instances[0].y += 3;
	//img->instances[0].z -= 3;
	mlx_set_instance_depth(img->instances, 230);
}

int	main()
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	mlx_image_t	*img2;
	mlx_texture_t	*texture = mlx_load_png("textures/wood.png");

	mlx = mlx_init(WIDTH, HEIGTH, "hi", false);
	img = mlx_new_image(mlx, 200, 200);
	img2 = mlx_texture_to_image(mlx, texture);
	mlx_put_pixel(img, 2, 2, 0xFFFFFFFF);
	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
	mlx_image_to_window(mlx, img, 0, 0);
	mlx_image_to_window(mlx, img2, 50, 50);
	//mlx_loop_hook(mlx, display_sth, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	
	printf("hi\n");
	return (0);
}