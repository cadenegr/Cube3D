/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadenegr <neo_dgri@hotmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 17:07:24 by cadenegr          #+#    #+#             */
/*   Updated: 2024/10/08 18:32:45 by cadenegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_STRUCTS_H
# define CUB3D_STRUCTS_H

struct	s_data;

typedef struct s_line
{
	int				x0;
	int				x1;
	double			ray_x1;
	int				y0;
	int				y1;
	double			ray_y1;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				err2;
	struct s_data	*data;
}	t_line;

typedef struct s_fov
{
	double				start_an;
	double				an_increment;
	double				curr_an;
	int					line_len;
	int					ray_x1;
	int					ray_y1;
	int					map_x;
	int					map_y;
	int					map_width;
	struct s_data		*data;
}	t_fov;

typedef struct s_map
{
	char				**map;
	char				*north;
	char				*south;
	char				*west;
	char				*east;
	char				*f_color;
	char				*c_color;
	char				*temp_north;
	char				*temp_south;
	char				*temp_west;
	char				*temp_east;
	char				*temp_f_color;
	char				*temp_c_color;
	int					floor_color;
	int					ceiling_color;
	int					before_line;
	int					longest_row;
	int					map_lines;
	struct s_data		*data;
}	t_map;

typedef struct s_player
{
	int				pos_x;
	int				pos_y;
	double			angle;
	int				player_count;
	char			face;
	struct s_data	*data;
}	t_player;

typedef struct s_texture
{
	void			*north_tex;
	void			*south_tex; 
	void			*east_tex;
	void			*west_tex;
	int				*north_data;
	int				*south_data;
	int				*east_data;
	int				*west_data;
	int				*default_wall_data;
	int				*texture_data;
	int				value_x;
	int				value_y;
	int				*previous_tex;
	int				prev_tex_x;
	int				width;
	int				height;
	int				no;
	int				so;
	int				ea;
	int				we;
	int				f;
	int				c;
	struct s_data	*data;
}	t_tex;

typedef struct s_render3d
{
	int				start_x;
	int				ray_width;
	float			correct_dist;
	int				wall_height;
	int				wall_top;
	int				wall_bottom;
	int				texture_y;
	int				color;
	int				ray_col;
	int				y;
	int				*texture_data;
	struct s_data	*data;
}	t_3d;

typedef struct s_image
{
	void			*img;
	void			*img3d;
	void			*addr;
	int				bpp;
	int				szl;
	int				endian;
	int				color;
	double			ppd;
	struct s_data	*data;
}	t_image;

typedef struct s_ray
{
	float			angle;
	int				distance;
	int				ray_sx;
	int				ray_sy;
	int				ray_x1;
	int				ray_y1;
	struct s_data	*data;
}	t_ray;

typedef struct s_data
{
	void		*mlx;
	void		*window;
	t_line		line;
	t_fov		fov;
	t_map		map;
	t_player	player;
	t_image		image;
	t_ray		*rays;
	t_tex		tex;
	t_3d		r3d;
}	t_data;
#endif