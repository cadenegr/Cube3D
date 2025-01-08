/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_tex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:56:09 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/10 12:08:29 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_surface_part2(t_data *data, int x, int type)
{
	int	start;

	data->tex.value_x = fabs(fmod(data->rays[x].ray_x1, TILE_SIZE));
	data->tex.value_y = fabs(fmod(data->rays[x].ray_y1, TILE_SIZE));
	start = x;
	if (type == 2)
	{
		if (data->tex.value_y == TILE_SIZE - 1)
		{
			if (data->rays[start].ray_y1 == data->rays[start - 1].ray_y1)
				if (data->rays[start].ray_y1 == data->rays[start + 1].ray_y1)
					return (1);
		}
		else
		{
			if (data->rays[start].ray_y1 == data->rays[start + 1].ray_y1)
				if (data->rays[start].ray_y1 == data->rays[start - 1].ray_y1)
					return (1);
		}
	}
	return (0);
}

int	check_surface(t_data *data, int x, int type)
{
	int	start;

	data->tex.value_x = fabs(fmod(data->rays[x].ray_x1, TILE_SIZE));
	data->tex.value_y = fabs(fmod(data->rays[x].ray_y1, TILE_SIZE));
	start = x;
	if (type == 1)
	{
		if (data->tex.value_x == TILE_SIZE - 1)
		{
			if (data->rays[start].ray_x1 == data->rays[start - 1].ray_x1)
				if (data->rays[start].ray_x1 == data->rays[start + 1].ray_x1)
					return (1);
		}
		else
		{
			if (data->rays[start].ray_x1 == data->rays[start + 1].ray_x1)
				if (data->rays[start].ray_x1 == data->rays[start - 1].ray_x1)
					return (1);
		}
	}
	return (check_surface_part2(data, x, type));
}

int	*select_texture_part2(t_data *data, int x, int *texture_x)
{
	if ((data->tex.value_x == TILE_SIZE - 1 || data->tex.value_x == 0))
	{
		if (data->tex.value_y == TILE_SIZE - 1 || data->tex.value_y == 0)
		{
			if (check_surface(data, x, 2) == 0)
			{
				if (data->tex.value_x == TILE_SIZE - 1)
					data->tex.texture_data = data->tex.west_data;
				if (data->tex.value_x == 0)
					data->tex.texture_data = data->tex.east_data;
				*texture_x = (int)(fmod(data->rays[x].ray_y1, TILE_SIZE)
						/ TILE_SIZE * data->tex.width);
			}
		}
		else
		{
			if (data->tex.value_x == TILE_SIZE - 1)
				data->tex.texture_data = data->tex.west_data;
			if (data->tex.value_x == 0)
				data->tex.texture_data = data->tex.east_data;
			*texture_x = (int)(fmod(data->rays[x].ray_y1, TILE_SIZE)
					/ TILE_SIZE * data->tex.width);
		}
	}
	return (data->tex.texture_data);
}

int	*select_texture(t_data *data, int x, int *texture_x)
{
	if ((data->tex.value_y == TILE_SIZE - 1 || data->tex.value_y == 0))
	{
		if (data->tex.value_x == TILE_SIZE - 1 || data->tex.value_x == 0)
		{
			if (check_surface(data, x, 1) == 0)
			{
				if (data->tex.value_y == TILE_SIZE - 1)
					data->tex.texture_data = data->tex.north_data;
				if (data->tex.value_y == 0)
					data->tex.texture_data = data->tex.south_data;
				*texture_x = (int)(fmod(data->rays[x].ray_x1, TILE_SIZE)
						/ TILE_SIZE * data->tex.width);
			}
		}
		else
		{
			if (data->tex.value_y == TILE_SIZE - 1)
				data->tex.texture_data = data->tex.north_data;
			if (data->tex.value_y == 0)
				data->tex.texture_data = data->tex.south_data;
			*texture_x = (int)(fmod(data->rays[x].ray_x1, TILE_SIZE)
					/ TILE_SIZE * data->tex.width);
		}
	}
	return (select_texture_part2(data, x, texture_x));
}
