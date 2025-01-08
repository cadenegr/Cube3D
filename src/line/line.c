/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:34:25 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/07 17:33:25 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_line_values(t_data *data, int x)
{
	data->line.dx = abs(data->line.x1 - data->line.x0);
	data->line.dy = abs(data->line.y1 - data->line.y0);
	if (data->line.x0 < data->line.x1)
	{
		data->line.sx = 1;
		data->rays[x].ray_sx = 1;
	}
	else
	{
		data->line.sx = -1;
		data->rays[x].ray_sx = -1;
	}
	if (data->line.y0 < data->line.y1)
	{
		data->line.sy = 1;
		data->rays[x].ray_sy = 1;
	}
	else
	{
		data->line.sy = -1;
		data->rays[x].ray_sy = -1;
	}
	data->line.err = data->line.dx - data->line.dy;
}

int	check_corner_collision_part2(t_data *data, int map_x, int map_y)
{
	if (data->map.map[map_y][(data->line.x0 + data->line.sx)
		/ TILE_SIZE] != '0')
	{
		data->line.x0 = ((data->line.x0 + data->line.sx)
				/ TILE_SIZE) * TILE_SIZE;
		return (1);
	}
	if (data->map.map[(data->line.y0 + data->line.sy)
			/ TILE_SIZE][map_x] != '0')
	{
		data->line.y0 = ((data->line.y0 + data->line.sy)
				/ TILE_SIZE) * TILE_SIZE;
		return (1);
	}
	return (0);
}

int	check_corner_collision(t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = data->line.x0 / TILE_SIZE;
	map_y = data->line.y0 / TILE_SIZE;
	if (data->map.map[map_y][map_x] != '0')
	{
		if (data->line.sx < 0)
			data->line.x0 = map_x * TILE_SIZE + TILE_SIZE;
		else
			data->line.x0 = map_x * TILE_SIZE;
		if (data->line.sy < 0)
			data->line.y0 = map_y * TILE_SIZE + TILE_SIZE;
		else
			data->line.y0 = map_y * TILE_SIZE;
		return (1);
	}
	return (check_corner_collision_part2(data, map_x, map_y));
}

int	bresenham_algorithm(t_data *data)
{
	data->line.err2 = data->line.err * 2;
	if (data->line.err2 > -data->line.dy)
	{
		data->line.err -= data->line.dy;
		data->line.x0 += data->line.sx;
	}
	if (data->line.err2 < data->line.dx)
	{
		data->line.err += data->line.dx;
		data->line.y0 += data->line.sy;
	}
	if (!(data->line.err2 > -data->line.dy)
		&& !(data->line.err2 < data->line.dx))
		return (1);
	return (0);
}

void	draw_line(t_data *data, int x)
{
	int	poser;

	draw_line_values(data, x);
	while (1)
	{
		if (data->line.x0 >= 0 && data->line.x0
			< (SCR_WIDTH) && data->line.y0 >= 0 && data->line.y0 < SCR_HEIGHT)
			poser = 1;
		if (data->line.x0 == data->line.x1 && data->line.y0 == data->line.y1)
			break ;
		if (bresenham_algorithm(data))
			break ;
		if (check_corner_collision(data))
			break ;
	}
}
