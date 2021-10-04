#ifndef SO_LONG_H
# define SO_LONG_H

# include <libft.h>
# include <get_next_line.h>
# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
	int			w;
	int			h;
}				t_data;

typedef struct		s_rndr
{
	unsigned int	**sheet;
	t_data			*tex;
}					t_rndr;

typedef struct		s_conf
{
	char			*file;
	unsigned int	res_w;
	unsigned int	res_h;
	char			*path_ex;
	char			*path_he;
	char			*path_it;
	char			*path_wa;
	char			**map;
	unsigned int	map_w;
	unsigned int	map_h;
	int				is_bmp;
	char			player;
	int				end_map;
}					t_conf;

typedef	struct	s_sprite
{
	t_data	tex;
	int		pos;
	float	texposx;
	float	texposy;
	float	ratio;	
}				t_sprite;

typedef struct	s_map
{
	size_t		width;
	size_t		height;
	char		**map;
	int			hero_pos[2];
	size_t		move_count;
}				t_map;

typedef struct	s_env
{
	t_conf			*conf;
	t_data			img;
	t_data			tex[4];
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

void		ft_error(char *str, t_env *env);


int			key_press(int keycode, t_env *env);
int			key_release(int keycode, t_env *env);
int			close_window(t_env *env);
void		ft_clear_env(t_env *env);
void		ft_puterr(char *str);
int			set_to_zero(size_t size, void *ptr);


#endif