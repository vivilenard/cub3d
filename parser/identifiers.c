/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekulichk <ekulichk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:15:13 by ekulichk          #+#    #+#             */
/*   Updated: 2023/09/04 15:38:07 by ekulichk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "../include/parser.h"
#include "../libft/libft.h"
#include "../MLX42/include/MLX42/MLX42.h"

int	get_identifier(t_map_set *map_set, char *line)
{
	int			i;
	int			len;
	char		**result;

	i = 0;
	len = ft_strlen(line);
	if (len >= 2)
		line[len - 1] = '\0';
	else
		return (printf("Error: wrong identifier\n"), EXIT_FAILURE);
	result = ft_split(line, ' ');
	if (result == NULL)
		return (printf("Error: wrong identifier\n"), EXIT_FAILURE);
	while (result[i])
		i++;
	if (i != 2 || set_identifier(map_set, result))
		return (free_split(result, i),
			printf("Error: wrong identifier\n"), EXIT_FAILURE);
	map_set->identifier++;
	free_split(result, i);
	return (EXIT_SUCCESS);
}

int	set_identifier(t_map_set *map_set, char **result)
{
	if (ft_strncmp(result[0], "NO\0", 3) == 0 && map_set->textures.no == NULL)
		map_set->textures.no = iden_copy(result[1]);
	else if (ft_strncmp(result[0], "SO\0", 3) == 0
		&& map_set->textures.so == NULL)
		map_set->textures.so = iden_copy(result[1]);
	else if (ft_strncmp(result[0], "EA\0", 3) == 0
		&& map_set->textures.ea == NULL)
		map_set->textures.ea = iden_copy(result[1]);
	else if (ft_strncmp(result[0], "WE\0", 3) == 0
		&& map_set->textures.we == NULL)
		map_set->textures.we = iden_copy(result[1]);
	else if (ft_strncmp(result[0], "F\0", 2) == 0 && !map_set->floor.is_color)
	{
		if (get_color(map_set, 'F', result[1]))
			return (EXIT_FAILURE);
	}
	else if (ft_strncmp(result[0], "C\0", 2) == 0
		&& !map_set->ceiling.is_color)
	{
		if (get_color(map_set, 'C', result[1]))
			return (EXIT_FAILURE);
	}
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	*iden_copy(char *src)
{
	int		len;
	char	*dst;

	len = ft_strlen(src);
	dst = malloc(sizeof(char) * (len + 1));
	ft_strlcpy(dst, src, len + 1);
	return (dst);
}
