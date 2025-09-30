/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:25:30 by cadenegr          #+#    #+#             */
/*   Updated: 2025/09/30 16:25:43 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	create_color_from_string(const char *color_str)
{
	int	r;
	int	g;
	int	b;
	int	i;

	r = 0;
	g = 0;
	b = 0;
	i = 0;
	while (*color_str)
	{
		if (*color_str >= '0' && *color_str <= '9')
		{
			if (i == 0)
				r = r * 10 + (*color_str - '0');
			else if (i == 1)
				g = g * 10 + (*color_str - '0');
			else if (i == 2)
				b = b * 10 + (*color_str - '0');
		}
		else if (*color_str == ',')
			i++;
		color_str++;
	}
	return ((r << 16) | (g << 8) | b);
}

void	make_null(t_data *data)
{
	if (data->map.temp_north)
		free(data->map.temp_north);
	if (data->map.temp_south)
		free(data->map.temp_south);
	if (data->map.temp_east)
		free(data->map.temp_east);
	if (data->map.temp_west)
		free(data->map.temp_west);
	if (data->map.temp_c_color)
		free(data->map.temp_c_color);
	if (data->map.temp_f_color)
		free(data->map.temp_f_color);
}

int	trim_unnecesary_spaces(t_data *data)
{
	if (!data->map.temp_north || !data->map.temp_south || !data->map.temp_east)
		return (1);
	if (!data->map.temp_west || !data->map.temp_c_color
		|| !data->map.temp_f_color)
		return (1);
	data->map.north = ft_strtrim(data->map.temp_north, "\n");
	data->map.south = ft_strtrim(data->map.temp_south, "\n");
	data->map.east = ft_strtrim(data->map.temp_east, "\n");
	data->map.west = ft_strtrim(data->map.temp_west, "\n");
	data->map.c_color = ft_strtrim(data->map.temp_c_color, "\n");
	data->map.f_color = ft_strtrim(data->map.temp_f_color, "\n");
	make_null(data);
	data->map.temp_north = ft_strtrim(data->map.north, " ");
	data->map.temp_south = ft_strtrim(data->map.south, " ");
	data->map.temp_east = ft_strtrim(data->map.east, " ");
	data->map.temp_west = ft_strtrim(data->map.west, " ");
	data->map.ceiling_color = create_color_from_string(data->map.c_color);
	data->map.floor_color = create_color_from_string(data->map.f_color);
	return (0);
}

int	check_if_map_begin(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strchr(" 1\n", line[i]) == NULL)
			return (1);
		else
			i++;
	}
	if (ft_strchr(line, '1') == NULL)
		return (1);
	return (0);
}

int	before_map(char *map, t_data *data)
{
	char	*line;
	int		fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (perror("Error!\nCannot open map."), 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line || get_tex_path(line, data))
		{
			if (!check_if_map_begin(line))
				break ;
			if (line)
				free (line);
			return (perror("Error!\n.cub file not with correct format!"), 1);
		}
		data->map.before_line++;
		free (line);
		line = NULL;
	}
	if (line)
		free (line);
	close (fd);
	return (0);
}
