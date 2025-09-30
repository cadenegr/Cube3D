/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:31:56 by cadenegr          #+#    #+#             */
/*   Updated: 2025/09/30 16:08:41 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	read_map(char *map, int start)
{
	char	*line;
	int		fd;
	int		height;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (perror("Error!\nCannot open map."), 1);
	height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strchr(line, '1') == NULL && height > start)
		{
			free (line);
			return (close(fd), perror("Error!\nInvaid map format."), -42);
		}
		free (line);
		height++;
	}
	close (fd);
	free (line);
	return (height - start);
}

int	map_maker(int fd, char **map, int start)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	while (1)
	{
		line = get_next_line (fd);
		if (!line)
			break ;
		if (i >= start)
			map[i - (start)] = ft_strtrim(line, "\n");
		free (line);
		i++;
	}
	map[i - (start)] = NULL;
	if (line)
	{
		free (line);
		line = NULL;
	}
	return (0);
}

int	save_map(char *map, t_data *data)
{
	int		fd;
	int		height;

	height = read_map(map, data->map.before_line);
	if (height == -42)
		return (1);
	fd = open (map, O_RDONLY);
	if (fd < 0)
		return (1);
	data->map.map = (char **)malloc(sizeof(char *) * (height + 1));
	if (!data->map.map)
		return (perror("Error!\nMalloc fail to allocate memory for map."), 1);
	data->map.map_lines = height;
	map_maker(fd, data->map.map, data->map.before_line);
	close (fd);
	return (0);
}

int	parse_map(int ac, char *map, t_data *data)
{
	if (init_data(data))
		return (1);
	if (ac != 2)
		return (perror("Error!\nMust include (only one) Argument!"), 1);
	if (!ft_strnstr(map, ".cub\0", ft_strlen(map)))
		return (perror("Error!\nMap should be a '.cub' file!"), 1);
	if (before_map(map, data))
		return (1);
	if (trim_unnecesary_spaces(data))
		return (1);
	if (save_map(map, data))
		return (1);
	if (validate_map(data))
		return (1);
	return (0);
}
