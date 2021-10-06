/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhenry <mhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 23:15:27 by mhenry            #+#    #+#             */
/*   Updated: 2021/10/06 23:46:57 by mhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <libft.h>
# include <get_next_line.h>
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}				t_data;

typedef struct s_conf
{
	char			*file;
	unsigned int	res_w;
	unsigned int	res_h;
	char			*path_ex;
	char			*path_he;
	char			*path_it;
	char			*path_wa;
	char			*path_end;
	char			**map;
	unsigned int	map_w;
	unsigned int	map_h;
}					t_conf;

typedef struct s_env
{
	t_conf			*conf;
	t_data			img;
	t_data			tex[4];
	t_data			end;
	t_data			*cur_tex;
	unsigned int	**sheet;
	int				hero_pos[2];
	size_t			move_count;
	size_t			collectibles;
	void			*mlx;
	void			*win;
	int				end_level;
	int				left;
	int				right;
	int				up;
	int				down;
}				t_env;

void				ft_error(char *str, t_env *env);
int					key_press(int keycode, t_env *env);
int					key_release(int keycode, t_env *env);
int					close_window(t_env *env);
void				ft_clear_env(t_env *env);
void				ft_puterr(char *str);
int					check_map(t_env *env);
void				check_args(int argc, t_env *env);
void				check_fd(char **argv, t_env *env);
int					missing_character(char **map);
void				my_mlx_init(t_env *env);
void				init_textures1(t_env *env);
void				init_textures2(t_env *env);
int					not_well_circled(char **map);
int					wrong_character(char **map);
int					map_not_rectangular(char **map);
int					map_too_small(char **map);
void				ft_clear_env(t_env *env);
void				ft_clear_tex(t_env *env);
void				ft_clear_conf(t_env *env);
void				display_move_count(t_env *env);
void				parse_map(t_env *env);
void				map_len(t_env *env, int fd);
int					set_to_zero(size_t size, void *ptr);
void				set_conf(t_env *env);
void				set_player_pos(t_env *env);
void				put_end_title(t_env *env);
void				draw_image(t_env *env);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				next_tex(t_env *env, size_t i, size_t j);
int					pick_tex_color(t_env *env, int y, int x);
void				put_end_title(t_env *env);
void				update_hero_pos(t_env *env);
void				move_up(t_env *env, int *up);
void				move_down(t_env *env, int *down);
void				move_right(t_env *env, int *right);
void				move_left(t_env *env, int *left);

#endif