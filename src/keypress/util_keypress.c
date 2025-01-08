/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_keypress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:10:09 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/07 19:15:16 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall_special_case(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;
	int	neg_map_x;
	int	neg_map_y;

	map_x = floor((x + (MOVE_STEP)) / TILE_SIZE);
	map_y = floor((y + (MOVE_STEP)) / TILE_SIZE);
	neg_map_x = floor((x - (MOVE_STEP)) / TILE_SIZE);
	neg_map_y = floor((y - (MOVE_STEP)) / TILE_SIZE);
	if (!ft_strchr("0", data->map.map[map_y][map_x]))
		return (1);
	if (!ft_strchr("0", data->map.map[neg_map_y][neg_map_x]))
		return (1);
	return (0);
}

int	is_wall(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x >= SCR_WIDTH || y < 0 || y >= SCR_HEIGHT)
		return (1);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (!ft_strchr("0", data->map.map[map_y][map_x]))
		return (1);
	return (is_wall_special_case(data, x, y));
}

int	rotation(int keycode, t_data *data)
{
	if (keycode == 65361)
		data->player.angle -= ROTATE_STEP;
	if (keycode == 65363)
		data->player.angle += ROTATE_STEP;
	if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	if (data->player.angle >= 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	return (0);
}

int	movements(int keycode, t_data *data, int *new_x, int *new_y)
{
	if (keycode == 119)
	{
		*new_x += floor(cos(data->player.angle) * MOVE_STEP);
		*new_y += floor(sin(data->player.angle) * MOVE_STEP);
	}
	if (keycode == 115)
	{
		*new_x -= floor(cos(data->player.angle) * MOVE_STEP);
		*new_y -= floor(sin(data->player.angle) * MOVE_STEP);
	}
	if (keycode == 97) 
	{
		*new_x += round(cos(data->player.angle - M_PI / 2) * MOVE_STEP);
		*new_y += round(sin(data->player.angle - M_PI / 2) * MOVE_STEP);
	}
	if (keycode == 100)
	{
		*new_x += round(cos(data->player.angle + M_PI / 2) * MOVE_STEP);
		*new_y += round(sin(data->player.angle + M_PI / 2) * MOVE_STEP);
	}
	return (rotation (keycode, data));
}

int	window_fts(t_data *data)
{
	if (data->image.img)
		mlx_destroy_image(data->mlx, data->image.img);
	data->image.img = mlx_new_image(data->mlx, SCR_WIDTH, SCR_HEIGHT);
	data->image.addr = (int *)mlx_get_data_addr(data->image.img, \
		&data->image.bpp, &data->image.szl, &data->image.endian);
	render_fov(data);
	render_3d_view(data);
	return (0);
}
