/* *************************************************		if (line[j] != '1' && line[j] != ' ' && line[j] != '\n')
			return (perror("Error!\nInvalid map format."), 1);*********************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:01:01 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/10 13:54:56 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	inspect_left_right(char *line, int place, int height)
{
	if (place == 0 || place == height - 1)
		return (0);
	place = 0;
	while (line[place])
	{
		if (line[place] == '1')
			break ;
		else if (line[place] == ' ')
			place++;
		else
			return (perror("Error!\nInvalid map format."), 1);
	}
	place = ft_strlen(line);
	while (place >= 0)
	{
		if (line[place] == '1')
			break ;
		else if (line[place] == ' ' || line[place] == '\n'
			|| line[place] == '\0')
			place--;
		else
			return (perror("Error!\nInvalid map format."), 1);
	}
	return (0);
}

int	inspect_edges(char *line, int height)
{
	static int	i = 0;
	int			j;

	j = 0;
	if (i == 0 || i == height - 1)
	{
		while (line[j])
		{
			if (line[j] != '1' && line[j] != ' ' && line[j] != '\n')
				return (perror("Error!\nInvaild map format."), 1);
			j++;
		}
	}
	i++;
	return (inspect_left_right(line, i - 1, height));
}

int	check_around(char **map, int y, int x)
{
	int	var;
	int	len;

	var = 0;
	len = ft_strlen(map[y + 1]);
	if (len > x)
		if (len >= x && ft_strchr("01NSEW", map[y + 1][x]))
			var++;
	if (ft_strchr("01NSEW", map[y][x + 1]))
		var++;
	len = ft_strlen(map[y - 1]);
	if (len > x)
		if (ft_strchr("01NSEW", map[y - 1][x]))
			var++;
	if (ft_strchr("01NSEW", map[y][x - 1]))
		var++;
	if (var == 4)
		return (0);
	return (1);
}

int	player_info(t_data *data, int i, int j)
{
	data->player.pos_x = j * TILE_SIZE + (TILE_SIZE / 2);
	data->player.pos_y = i * TILE_SIZE + (TILE_SIZE / 2);
	data->player.face = data->map.map[i][j];
	if (data->map.map[i][j] == 'N')
		data->player.angle = M_PI * 1.5;
	else if (data->map.map[i][j] == 'S')
		data->player.angle = M_PI / 2;
	else if (data->map.map[i][j] == 'E')
		data->player.angle = 0;
	else if (data->map.map[i][j] == 'W')
		data->player.angle = M_PI;
	data->player.player_count++;
	data->map.map[i][j] = '0';
	return (0);
}

int	validate_map(t_data *data)
{
	int	i;
	int	j;
	int	len;

	i = -1;
	while (++i < data->map.map_lines)
	{
		len = ft_strlen(data->map.map[i]);
		if (len > data->map.longest_row)
			data->map.longest_row = len;
		if (inspect_edges(data->map.map[i], data->map.map_lines))
			return (1);
		j = -1;
		while (data->map.map[i][++j])
		{
			if (ft_strchr("01NSEW \n", data->map.map[i][j]) == NULL)
				return (perror("Error!\nInvalid character in map.->"), 1);
			if (ft_strchr("NSEW", data->map.map[i][j]))
				player_info(data, i, j);
			if (data->map.map[i][j] == '0')
				if (check_around(data->map.map, i, j))
					return (perror("Error!\nInvalid map."), 1);
		}
	}
	return (data->player.player_count - 1);
}
