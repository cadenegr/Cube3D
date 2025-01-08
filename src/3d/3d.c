/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:02:16 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/09 15:03:18 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_pixel(t_image *img, int x, int y, int color)
{
	char	*pixel;
	int		index;

	if (x < 0 || y < 0 || x >= SCR_WIDTH || y >= SCR_HEIGHT)
		return ;
	index = (y * img->szl) + (x * (img->bpp / 8));
	pixel = img->addr + index;
	*(unsigned int *)pixel = color;
}

void	ft_render_3d_part2(t_data *data, t_3d *r3d, int x)
{
	int	y;

	y = -1;
	while (++y < SCR_HEIGHT)
	{
		if (y < r3d->wall_top)
			put_pixel(&data->image, r3d->start_x + (x * r3d->ray_width)
				+ r3d->ray_col, y, data->map.ceiling_color);
		else if (y > r3d->wall_bottom)
			put_pixel(&data->image, r3d->start_x + (x * r3d->ray_width)
				+ r3d->ray_col, y, data->map.floor_color);
		else
		{
			r3d->texture_y = (int)((y - r3d->wall_top)
					* ((float)data->tex.height / r3d->wall_height));
			if (r3d->texture_data)
				r3d->color = r3d->texture_data[r3d->texture_y
					* data->tex.width + data->tex.prev_tex_x];
			else
				r3d->color = data->tex.previous_tex[r3d->texture_y
					* data->tex.width + data->tex.prev_tex_x];
			put_pixel(&data->image, r3d->start_x + (x * r3d->ray_width)
				+ r3d->ray_col, y, r3d->color);
		}
	}
}

void	render_3d_values(t_data *data, t_3d *r3d, int x)
{
	r3d->correct_dist = data->rays[x].distance
		* cos(data->player.angle - data->rays[x].angle);
	r3d->wall_height = (int)((TILE_SIZE / r3d->correct_dist)
			* data->image.ppd);
	r3d->wall_top = (SCR_HEIGHT / 2) - (r3d->wall_height / 2);
	if (r3d->wall_top < 0)
		r3d->wall_top = 0;
	r3d->wall_bottom = (SCR_HEIGHT / 2) + (r3d->wall_height / 2);
	if (r3d->wall_bottom >= SCR_HEIGHT)
		r3d->wall_bottom = SCR_HEIGHT - 1;
	r3d->texture_data = NULL;
	data->tex.value_x = fabs(fmod(data->rays[x].ray_x1, TILE_SIZE));
	data->tex.value_y = fabs(fmod(data->rays[x].ray_y1, TILE_SIZE));
	r3d->texture_data = select_texture(data, x, &data->tex.prev_tex_x);
	if (r3d->texture_data == NULL)
		data->tex.previous_tex = data->tex.default_wall_data;
}

void	render_3d_view(t_data *data)
{
	t_3d	r3d;
	int		x;

	x = -1;
	r3d.start_x = 0;
	r3d.ray_width = SCR_WIDTH / NUM_RAYS;
	while (++x < NUM_RAYS)
	{
		render_3d_values(data, &r3d, x);
		r3d.ray_col = -1;
		while (++r3d.ray_col < r3d.ray_width)
			ft_render_3d_part2(data, &r3d, x);
	}
	mlx_put_image_to_window(data->mlx, data->window, data->image.img, 0, 0);
}
