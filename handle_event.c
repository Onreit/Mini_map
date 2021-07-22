/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjalo <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 10:11:51 by tjalo             #+#    #+#             */
/*   Updated: 2021/02/02 16:27:46 by tjalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/* Pour linux changer les valeurs de key et de current_key */

int		key_pressed(int key, t_game *game)
{
	if (key == W || key == A || key == S || key == D || key == ESC)
		game->current_key = key;
	printf("[%d]\n", key);
	return (1);
}

int		key_release(int key, t_game *game)
{
	if (key == W || key == A || key == S || key == D)
		game->current_key = INT_MIN;
	return (1);
}

int		collision(int key, t_game *game)
{
	float tmp_y;
	float tmp_x;

	tmp_y = game->player->posY;
	tmp_x = game->player->posX;
	if (key == W)
		tmp_y -= MOVE;
	if (key == S)
		tmp_y += MOVE;
	if (key == A)
		tmp_x -= MOVE;
	if (key == D)
		tmp_x += MOVE;
	return (game->map->l_map[(int)tmp_y][(int)tmp_x] == 1);
}

/*int	hit_wall(t_game *game)
{
	int	x;
	int	y;


	y = (int)((game->win->height / game->map->nb_row) * (game->player->posY));
	x = (int)((game->win->width / game->map->nb_col) * (game->player->posX));

	return (0);
}*/

void	draw_line(t_game *game)
{
	int		x;
	int		y;

	y = ((game->win->height / game->map->nb_row) * (game->player->posY));
	x = ((game->win->width / game->map->nb_col) * (game->player->posX));
	if (game->player->dir == 'W')
		while (x > 0)
		{
			my_mlx_pixel_put(game->data, x, y, 0x00FF00);
			x--;
		}	
	if (game->player->dir == 'N')
		while (y > 0)
		{
			my_mlx_pixel_put(game->data, x, y, 0x00FF00);
			y--;
		}
}

void	move(int key, t_game *game)
{
	if (key == W && !collision(key, game))
		game->player->posY -= MOVE;
	if (key == S && !collision(key, game))
		game->player->posY += MOVE;
	if (key == A && !collision(key, game))
		game->player->posX -= MOVE;
	if (key == D && !collision(key, game))
		game->player->posX += MOVE;
}

int		main_loop(t_game *game)
{
	if (game->current_key == W || game->current_key == A ||
			game->current_key == S || game->current_key == D)
		move(game->current_key, game);
	if (game->current_key == ESC)
	{
		mlx_destroy_window(game->win->mlx_ptr, game->win->win_ptr);
		exit_failure("Clear game");
		clear_game(game);
	}
	mini_map(game);
	draw_line(game);
	mlx_put_image_to_window(game->win->mlx_ptr,game->win->win_ptr, game->data->img, 0, 0);
	return (1);
}
