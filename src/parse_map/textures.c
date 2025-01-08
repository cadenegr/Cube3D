/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:26:00 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/08 18:53:20 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_textures_2(t_data *data)
{
	data->tex.default_wall_data = mlx_xpm_file_to_image(data->mlx, DEFAULT_WALL,
			&data->tex.width, &data->tex.height);
	if (!data->tex.default_wall_data)
		return (perror("Error!\nXPM image didnt load."), 1);
	data->tex.default_wall_data = (int *)mlx_get_data_addr
		(data->tex.default_wall_data, &data->image.bpp,
			&data->image.szl, &data->image.endian);
	return (0);
}

int	init_textures(t_data *data)
{
	data->tex.north_tex = mlx_xpm_file_to_image(data->mlx, data->map.temp_north,
			&data->tex.width, &data->tex.height);
	if (!data->tex.north_tex)
		return (perror("Error!\nXPM NO image didnt load."), 1);
	data->tex.north_data = (int *)mlx_get_data_addr(data->tex.north_tex,
			&data->image.bpp, &data->image.szl, &data->image.endian);
	data->tex.south_tex = mlx_xpm_file_to_image(data->mlx, data->map.temp_south,
			&data->tex.width, &data->tex.height);
	if (!data->tex.south_tex)
		return (perror("Error!\nXPM SO image didnt load."), 1);
	data->tex.south_data = (int *)mlx_get_data_addr(data->tex.south_tex,
			&data->image.bpp, &data->image.szl, &data->image.endian);
	data->tex.east_tex = mlx_xpm_file_to_image(data->mlx, data->map.temp_east,
			&data->tex.width, &data->tex.height);
	if (!data->tex.east_tex)
		return (perror("Error!\nXPM EA image didnt load."), 1);
	data->tex.east_data = (int *)mlx_get_data_addr(data->tex.east_tex,
			&data->image.bpp, &data->image.szl, &data->image.endian);
	data->tex.west_tex = mlx_xpm_file_to_image(data->mlx, data->map.temp_west,
			&data->tex.width, &data->tex.height);
	if (!data->tex.west_tex)
		return (perror("Error!\nXPM WE image didnt load."), 1);
	data->tex.west_data = (int *)mlx_get_data_addr(data->tex.west_tex,
			&data->image.bpp, &data->image.szl, &data->image.endian);
	return (0);
}

int	get_tex_path_2(t_data *data)
{
	if (data->map.temp_north)
		data->tex.no++;
	if (data->map.temp_south)
		data->tex.so++;
	if (data->map.temp_east)
		data->tex.ea++;
	if (data->map.temp_west)
		data->tex.we++;
	if (data->map.temp_c_color)
		data->tex.c++;
	if (data->map.temp_f_color)
		data->tex.f++;
	return (0);
}

int	get_tex_path(char *line, t_data *data)
{
	if (line[0] == '\n')
		return (0);
	else if (ft_strnstr(line, "NO", 2) && data->tex.no == 0)
		data->map.temp_north = ft_substr(line, 2, (ft_strlen(line)));
	else if (ft_strnstr(line, "SO", 2) && data->tex.so == 0)
		data->map.temp_south = ft_substr(line, 2, (ft_strlen(line)));
	else if (ft_strnstr(line, "WE", 2) && data->tex.we == 0)
		data->map.temp_west = ft_substr(line, 2, (ft_strlen(line)));
	else if (ft_strnstr(line, "EA", 2) && data->tex.ea == 0)
		data->map.temp_east = ft_substr(line, 2, (ft_strlen(line)));
	else if (ft_strnstr(line, "C", 1) && data->tex.c == 0)
		data->map.temp_c_color = ft_substr(line, 1, (ft_strlen(line)));
	else if (ft_strnstr(line, "F", 1) && data->tex.f == 0)
		data->map.temp_f_color = ft_substr(line, 1, (ft_strlen(line)));
	else
		return (1);
	return (get_tex_path_2(data));
}
