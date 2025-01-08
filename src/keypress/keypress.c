/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 13:26:26 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/07 17:11:39 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	handle_close(t_data *data)
{
	mlx_destroy_window(data->mlx, data->window);
	exit (0);
	return (0);
}

int	handle_keypress(int keycode, t_data *data)
{
	int	new_x;
	int	new_y;

	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(data->mlx, data->window);
		return (exit(0), 0);
	}
	new_x = data->player.pos_x;
	new_y = data->player.pos_y;
	if (data->player.angle < 0)
		data->player.angle += 2 * M_PI;
	if (data->player.angle >= 2 * M_PI)
		data->player.angle -= 2 * M_PI;
	movements(keycode, data, &new_x, &new_y);
	if (!is_wall(data, new_x, new_y))
	{
		data->player.pos_x = new_x;
		data->player.pos_y = new_y;
	}
	return (0);
}
