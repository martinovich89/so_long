#include <so_long.h>
#include <sys/time.h>

# define WIDTH 1920
# define HEIGHT 1080

struct timeval tv;
struct timezone tz;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

int	frame_loop(t_env *env)
{
	ft_bzero(env->img->addr, sizeof(env->img->addr));
//	mlx_destroy_image(env->mlx, env->img->img);
//	env->img->img = mlx_new_image(env->mlx, WIDTH, HEIGHT);
//	env->img->addr = mlx_get_data_addr(env->img->img, &env->img->bpp, &env->img->line_length,
//								&env->img->endian);
	my_mlx_pixel_put(env->img, 5, 5, 0x00FF0000);

	gettimeofday(&tv, &tz);
	printf("%zu\n", tv.tv_sec * 1000000 + tv.tv_usec);
	mlx_put_image_to_window(env->mlx, env->win, env->img->img, 0, 0);
	return (0);
}

int	main(void)
{
	t_env	env;

	env.img = malloc(sizeof(env.img));
	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "Hello world!");
	env.img->img = mlx_new_image(env.mlx, WIDTH, HEIGHT);
	env.img->addr = mlx_get_data_addr(env.img->img, &env.img->bpp, &env.img->line_length,
								&env.img->endian);
	mlx_loop_hook(env.mlx, frame_loop, &env);
	mlx_loop(env.mlx);
}