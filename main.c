#include "include/cub3d.h"
#include "mlx.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_player(t_game *game)
{
	int	count_y;
	int	count_x;

	count_y = (int)((game->win->height / game->map->nb_row) * (game->player->posY - 0.25));
	while (count_y < (game->win->height / game->map->nb_row) * (game->player->posY + 0.25))
	{
		count_x = (int)((game->win->width / game->map->nb_col) * (game->player->posX - 0.25)); 
		while (count_x < (game->win->width / game->map->nb_col) * (game->player->posX + 0.25))
		{
			my_mlx_pixel_put(game->data, count_x, count_y, 0x00FF00);
			count_x++;
		}
		count_y++;
	}
}

void	mini_map(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->nb_row)
	{
		x = 0;
		while (x < game->map->nb_col)
		{
			mini_map_bis(game, x, y);
			x++;
		}
		y++;
	}
	draw_player(game);
}

void	mini_map_bis(t_game *game, int x, int y)
{
	int	count_x;
	int	count_y;

	count_y = (game->win->height / game->map->nb_row) * y;
	while (count_y < ((game->win->height / game->map->nb_row) * (y + 1)))
	{
		count_x = (game->win->width / game->map->nb_col) * x;
		while (count_x < ((game->win->width / game->map->nb_col) * (x + 1)))
		{
			if (count_y ==(game->win->height / game->map->nb_row) * y || count_x ==(game->win->width / game->map->nb_col) * x )
				my_mlx_pixel_put(game->data, count_x, count_y, 0x0);
			else if (game->map->l_map[y][x] == 0 && count_x != (game->win->width / game->map->nb_col) * (x + 1))
				my_mlx_pixel_put(game->data, count_x, count_y, 0xFFFFFF);
			else if (game->map->l_map[y][x] == 1)
				my_mlx_pixel_put(game->data, count_x, count_y, 0x0000FF);
			count_x++;
		}
		count_y++;
	}
}

int	main(int ac, char **av)
{
	t_game *gamer;

	if (!(gamer = (t_game *)malloc(sizeof(t_game))))
		return (0);
	init_game(gamer);
	if (ac != 2)
		return (0);
	parse_file(av[1], gamer);
	parse_map_bis(gamer);
	print_map(gamer->map->l_map, gamer->map->nb_row, gamer->map->nb_col);
	gamer->win->mlx_ptr = mlx_init();
	gamer->win->win_ptr = mlx_new_window(gamer->win->mlx_ptr, gamer->win->width, gamer->win->height, "mlx test");
	gamer->data->img = mlx_new_image(gamer->win->mlx_ptr, gamer->win->width, gamer->win->height);
	gamer->data->addr = mlx_get_data_addr(gamer->data->img, &gamer->data->bits_per_pixel, &gamer->data->line_length, &gamer->data->endian);
	mini_map(gamer);
	mlx_hook(gamer->win->win_ptr, 2, (1L<<0), key_pressed, gamer);
	mlx_hook(gamer->win->win_ptr, 3, (1L<<1), key_release, gamer);
	mlx_loop_hook(gamer->win->mlx_ptr, &main_loop, gamer);
	mlx_loop(gamer->win->mlx_ptr);
	return (0);
}
