/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 15:04:39 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/08 19:10:03 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_textures(t_data *data)
{
	if (data->tex.north_tex)
		mlx_destroy_image(data->mlx, data->tex.north_tex);
	if (data->tex.south_tex)
		mlx_destroy_image(data->mlx, data->tex.south_tex);
	if (data->tex.east_tex)
		mlx_destroy_image(data->mlx, data->tex.east_tex);
	if (data->tex.west_tex)
		mlx_destroy_image(data->mlx, data->tex.west_tex);
}

void	close_program_2(t_data *data)
{
	if (data->map.temp_north != NULL)
		free(data->map.temp_north);
	if (data->map.temp_south != NULL)
		free(data->map.temp_south);
	if (data->map.temp_east != NULL)
		free(data->map.temp_east);
	if (data->map.temp_west != NULL)
		free(data->map.temp_west);
	if (data->map.north != NULL)
		free(data->map.north);
	if (data->map.south != NULL)
		free(data->map.south);
	if (data->map.east != NULL)
		free(data->map.east);
	if (data->map.west != NULL)
		free(data->map.west);
	if (data->map.c_color != NULL)
		free(data->map.c_color);
	if (data->map.f_color != NULL)
		free(data->map.f_color);
}

void	close_program(t_data *data)
{
	ft_free_arr(data->map.map);
	free(data->rays);
	close_program_2(data);
	destroy_textures(data);
	if (data->window)
		mlx_destroy_window(data->mlx, data->window);
	if (data->mlx)
		free (data->mlx);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (parse_map(ac, av[1], &data))
		return (close_program(&data), EXIT_FAILURE);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (close_program(&data), EXIT_FAILURE);
	if (init_textures(&data))
		return (close_program(&data), EXIT_FAILURE);
	data.window = mlx_new_window(data.mlx, SCR_WIDTH, SCR_HEIGHT, "cub3D");
	if (!data.window)
		return (close_program(&data), EXIT_FAILURE);
	mlx_hook(data.window, KeyPress, KeyPressMask, handle_keypress, &data);
	mlx_hook (data.window, 17, 0, handle_close, &data);
	mlx_loop_hook(data.mlx, window_fts, &data);
	mlx_loop (data.mlx);
	return (close_program(&data), EXIT_SUCCESS);
}
