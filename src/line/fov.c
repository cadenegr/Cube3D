/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fov.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:33:15 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/02 17:12:53 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_fov_sec_loop_values(t_data *data, int i, int type)
{
	int	delta_x;
	int	delta_y;

	if (type == 1)
	{
		data->fov.ray_x1 = data->line.x0
			+ (int)(data->fov.line_len * cos(data->fov.curr_an));
		data->fov.ray_y1 = data->line.y0
			+ (int)(data->fov.line_len * sin(data->fov.curr_an));
	}
	if (type == 2)
		data->fov.map_y = data->fov.ray_y1 / TILE_SIZE;
	if (type == 3)
	{
		data->fov.map_width = ft_strlen(data->map.map[data->fov.map_y]);
		data->fov.map_x = data->fov.ray_x1 / TILE_SIZE;
	}
	if (type == 4)
	{
		delta_x = data->fov.ray_x1 - data->player.pos_x;
		delta_y = data->fov.ray_y1 - data->player.pos_y;
		data->rays[i].distance = sqrt(delta_x * delta_x + delta_y * delta_y);
		data->rays[i].ray_x1 = data->fov.ray_x1;
		data->rays[i].ray_y1 = data->fov.ray_y1;
	}
}

void	render_fov_sec_loop_values_end(t_data *data, int i)
{
	data->rays[i].angle = data->fov.curr_an;
	data->line.x1 = data->fov.ray_x1;
	data->line.y1 = data->fov.ray_y1;
}

void	render_fov_sec_loop(t_data *data, int i)
{
	while (data->fov.line_len < MAX_RAY_LENGTH)
	{
		render_fov_sec_loop_values(data, i, 1);
		if (data->fov.ray_x1 >= 0 && data->fov.ray_x1 < SCR_WIDTH
			&& data->fov.ray_y1 >= 0 && data->fov.ray_y1 < SCR_HEIGHT)
		{
			render_fov_sec_loop_values(data, i, 2);
			if (data->fov.map_y >= 0 && data->fov.map_y < data->map.map_lines
				&& data->map.map[data->fov.map_y] != NULL)
			{
				render_fov_sec_loop_values(data, i, 3);
				if (data->fov.map_x < data->fov.map_width)
				{
					if (data->map.map[data->fov.map_y][data->fov.map_x] != '0')
					{
						render_fov_sec_loop_values(data, i, 4);
						break ;
					}
				}
			}
		}
		data->fov.line_len += RAY_STEP;
	}
	render_fov_sec_loop_values_end(data, i);
}

void	render_fov(t_data *data)
{
	int	i;

	data->fov.an_increment = FOV_ANGLE / NUM_RAYS;
	data->fov.start_an = data->player.angle - (FOV_ANGLE / 2);
	i = 0;
	while (i < NUM_RAYS)
	{
		data->fov.curr_an = data->fov.start_an + i * data->fov.an_increment;
		data->line.x0 = data->player.pos_x;
		data->line.y0 = data->player.pos_y;
		data->line.x1 = data->line.x0;
		data->line.y1 = data->line.y0;
		data->fov.line_len = 0;
		render_fov_sec_loop(data, i);
		draw_line(data, i);
		i++;
	}
}
