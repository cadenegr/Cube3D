/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:07:53 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/09 14:45:48 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include "cub3d_structs.h"

# define SCR_WIDTH 1920
# define SCR_HEIGHT 1080
# define M_PI 3.14159265358979323846
# define FOV_ANGLE 1.047197551
# define NUM_RAYS 820
# define MAX_RAY_LENGTH 10000
# define RAY_STEP 1
# define ROTATE_STEP 0.1
# define ESC_KEY 65307
# define DISPLAY 0x191919
# define TILE_SIZE 32
# define MOVE_STEP 8
# define FOV 50.0
# define DEFAULT_WALL "./tex/WALL46.xpm"

//init.c
void	init_line_and_fov(t_line *line, t_fov *fov);
void	init_image(t_image *image, t_3d *r3d);
void	init_player(t_tex *tex);
void	init_map(t_player *player, t_map *map);
int		init_data(t_data *data);

//textures.c
int		init_textures(t_data *data);
int		create_color_from_string(const char *color_str);
int		trim_unnecesary_spaces(t_data *data);
int		get_tex_path(char *line, t_data *data);

//util_keypress.c
int		is_wall(t_data *data, int x, int y);
int		rotation(int keycode, t_data *data);
int		movements(int keycode, t_data *data, int *new_x, int *new_y);
int		window_fts(t_data *data);

//keypress
int		handle_close(t_data *data);
int		handle_keypress(int keycode, t_data *data);

//map.c
int		read_map(char *map, int start);
int		map_maker(int fd, char **map, int start);
int		save_map(char *map, t_data *data);
int		parse_map(int ac, char *map, t_data *data);

//elements_map.c
int		check_if_map_begin(char *line);
int		before_map(char *map, t_data *data);

//validate_map.c
int		inspect_left_right(char *line, int place, int height);
int		inspect_edges(char *line, int height);
int		check_around(char **map, int y, int x);
int		player_info(t_data *data, int i, int j);
int		validate_map(t_data *data);

//line.c
void	draw_line_values(t_data *data, int x);
int		check_corner_collision_part2(t_data *data, int map_x, int map_y);
int		check_corner_collision(t_data *data);
int		bresenham_algorithm(t_data *data);
void	draw_line(t_data *data, int x);

//fov.c
void	render_fov_sec_loop(t_data *data, int i);
void	render_fov(t_data *data);

//3d_tex.c
int		check_surface_part2(t_data *data, int x, int type);
int		check_surface(t_data *data, int x, int type);
int		*select_texture_part2(t_data *data, int x, int *texture_x);
int		*select_texture(t_data *data, int x, int *texture_x);

//3d.c
void	put_pixel(t_image *img, int x, int y, int color);
void	ft_render_3d_part2(t_data *data, t_3d *r3d, int x);
void	render_3d_values(t_data *data, t_3d *r3d, int x);
void	render_3d_view(t_data *data);

#endif