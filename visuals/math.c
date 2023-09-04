/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlenard <vlenard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:42:06 by vlenard           #+#    #+#             */
/*   Updated: 2023/09/04 14:42:07 by vlenard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/display.h"

double	delta_dist(double side)
{
	return (fabs(1 / side));
}

int	calculate_lineheight(double distance)
{
	return ((int)((HEIGTH / distance) * (90 / VIEW_ANGLE)));
}

t_color	to_rgbt(int r, int g, int b, int t)
{
	return ((r << 24) + (g << 16) + (b << 8) + t);
}
