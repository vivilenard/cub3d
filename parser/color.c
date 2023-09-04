/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:14:50 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/04 17:40:50 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/parser.h"
#include "../libft/libft.h"

int	get_color(t_map_set *map_set, char side, char *str)
{
	int		i;
	char	**colors;
	bool	is_default;

	i = 0;
	colors = ft_split(str, ',');
	if (colors == NULL)
		return (EXIT_FAILURE);
	is_default = false;
	while (colors[i])
		i++;
	if (i != 3)
		return (free_split(colors, i), EXIT_FAILURE);
	else
		set_color(map_set, side, colors, &is_default);
	free_split(colors, i);
	if (is_default)
		printf("Default color is using\n");
	return (EXIT_SUCCESS);
}

void	set_color(
	t_map_set *map_set, char side, char **colors, bool *is_default)
{
	if (side == 'F')
	{
		map_set->floor.color = get_rgba(get_channel(colors[0], is_default),
				get_channel(colors[1], is_default),
				get_channel(colors[2], is_default), 255);
		map_set->floor.is_color = true;
	}
	else if (side == 'C')
	{
		map_set->ceiling.color = get_rgba(get_channel(colors[0], is_default),
				get_channel(colors[1], is_default),
				get_channel(colors[2], is_default), 255);
		map_set->ceiling.is_color = true;
	}
}

int	get_channel(char *str, bool *is_default)
{
	int	temp;

	temp = ft_atoi(str);
	if (temp > 255 || temp < 0)
	{
		*is_default = true;
		return (0);
	}
	return (temp);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
