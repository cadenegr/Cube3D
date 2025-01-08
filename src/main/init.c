/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:44:53 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/08 18:32:45 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_line_and_fov(t_line *line, t_fov *fov)
{
	line->x0 = 0;
	line->x1 = 0;
	line->ray_x1 = 0;
	line->y0 = 0;
	line->y1 = 0;
	line->ray_y1 = 0;
	line->dx = 0;
	line->dy = 0;
	line->sx = 0;
	line->sy = 0;
	line->err = 0;
	line->err2 = 0;
	fov->start_an = 0;
	fov->an_increment = 0;
	fov->curr_an = 0;
	fov->line_len = 0;
	fov->ray_x1 = 0;
	fov->ray_y1 = 0;
	fov->map_x = 0;
	fov->map_y = 0;
	fov->map_width = 0;
}

void	init_image(t_image *image, t_3d *r3d)
{
	image->img = NULL;
	image->addr = NULL;
	image->bpp = 0;
	image->szl = 0;
	image->endian = 0;
	image->color = 0;
	image->img3d = NULL;
	image->ppd = (SCR_HEIGHT / 2) / tan(FOV / 2 * (M_PI / 180));
	r3d->start_x = 0;
	r3d->ray_width = 0;
	r3d->correct_dist = 0;
	r3d->wall_height = 0;
	r3d->wall_top = 0;
	r3d->wall_bottom = 0;
	r3d->texture_y = 0;
	r3d->color = 0;
	r3d->ray_col = 0;
	r3d->y = 0;
}

void	init_player(t_tex *tex)
{
	tex->north_tex = NULL;
	tex->south_tex = NULL; 
	tex->east_tex = NULL;
	tex->west_tex = NULL;
	tex->north_data = 0;
	tex->south_data = 0;
	tex->east_data = 0;
	tex->west_data = 0;
	tex->default_wall_data = 0;
	tex->width = 0;
	tex->height = 0;
	tex->texture_data = NULL;
	tex->previous_tex = NULL;
	tex->value_x = 0;
	tex->value_y = 0;
	tex->prev_tex_x = 0;
	tex->no = 0;
	tex->so = 0;
	tex->ea = 0;
	tex->we = 0;
	tex->f = 0;
	tex->c = 0;
}

void	init_map(t_player *player, t_map *map)
{
	player->pos_x = 0;
	player->pos_y = 0;
	player->angle = 0;
	player->player_count = 0;
	player->face = '\0';
	map->map = NULL;
	map->north = NULL;
	map->south = NULL;
	map->west = NULL;
	map->east = NULL;
	map->f_color = NULL;
	map->c_color = NULL;
	map->temp_north = NULL;
	map->temp_south = NULL;
	map->temp_west = NULL;
	map->temp_east = NULL;
	map->temp_f_color = NULL;
	map->temp_c_color = NULL;
	map->floor_color = 0;
	map->ceiling_color = 0;
	map->before_line = 0;
	map->map_lines = 0;
	map->longest_row = 0;
}

int	init_data(t_data *data)
{
	data->rays = malloc(sizeof(t_ray) * SCR_WIDTH);
	if (!data->rays)
		return (perror("Error!\n Malloc problem."), 1);
	data->mlx = NULL;
	data->window = NULL;
	init_map(&data->player, &data->map);
	init_player(&data->tex);
	init_image(&data->image, &data->r3d);
	init_line_and_fov(&data->line, &data->fov);
	return (0);
}
