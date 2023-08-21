
// void	free_split(char **str, int i)
// {
// 	while (i != 0)
// 	{
// 		free(str[i - 1]);
// 		i--;
// 	}
// 	free(str);
// }

// t_side	get_side(char *str)
// {
// 	if (ft_strncmp(str, "NO\0", 3) == 0)
// 		return (NORTH);
// 	if (ft_strncmp(str, "SO\0", 3) == 0)
// 		return (SOUTH);
// 	if (ft_strncmp(str, "EA\0", 3) == 0)
// 		return (EAST);
// 	if (ft_strncmp(str, "WE\0", 3) == 0)
// 		return (WEST);
// 	else
// 		return (NONE);
// }

// int	malloc2(size_t count, void **ptr)
// {
// 	*ptr = malloc(count);
// 	return (*ptr == NULL);
// }

// int	print_malloc_failed(void)
// {
// 	printf("Error: malloc failed\n");
// 	return (EXIT_FAILURE);
// }

// int read_identifiers_line(t_map_params *map_params, char *line)
// {
// 	if (map_params->identifier == 6)
// 		return (EXIT_SUCCESS);
// 	return (get_identifier(map_params, line));
// }

// int read_map_line(t_map_params *map_params, char *line)
// {
// 	if (map_params->identifier != 6)
// 		return (EXIT_SUCCESS);
// 	if (get_map(map_params, line))
// 		return (EXIT_FAILURE);
// 	map_params->map_start = true;
// 	map_params->height++;
// 	return (EXIT_SUCCESS);
// }

// int	read_map(t_map_params *map_params, int fd)
// {
// 	char	*line;

// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		if (*line == '\n')
// 		{
// 			if (map_params->map_start && !map_params->map_end)
// 				map_params->map_end = true;
// 		}
// 		else
// 		{
// 			if (read_identifiers_line(map_params, line))
// 				return (EXIT_FAILURE);
// 			if (read_map_line(map_params, line))
// 				return (EXIT_FAILURE);
// 		}
// 		if (*line != '\n' && map_params->map_end)
// 			return (free(line), printf("Error: empty line in a map content\n"),
// 				EXIT_FAILURE);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (EXIT_SUCCESS);
// }