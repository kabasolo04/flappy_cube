/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:24:45 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/06 19:47:59 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


static int random_num(int min, int max)
{
    return (rand() % (max - min + 1) + min);
}

char **create_walls(t_game *g)
{
	char **mod_map;
	int	wall_len;

	wall_len = random_num(g->lines - 12, g->lines - 6);
	mod_map = split_cpy(g->map);
	mod_map[wall_len - 1][18] = '0';
	mod_map[wall_len - 2][18] = '0';
	mod_map[wall_len - 3][18] = '0';
	return (mod_map);
}

static void	put_score(t_game *g, int n, int x, int y)
{
	int	i;

	i = 1;
	while (n > 0)
	{
		if (n % 10 == 0)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_0, x - 60 * i, y);
		if (n % 10 == 1)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_1, x - 60 * i, y);
		if (n % 10 == 2)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_2, x - 60 * i, y);
		if (n % 10 == 3)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_3, x - 60 * i, y);
		if (n % 10 == 4)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_4, x - 60 * i, y);
		if (n % 10 == 5)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_5, x - 60 * i, y);
		if (n % 10 == 6)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_6, x - 60 * i, y);
		if (n % 10 == 7)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_7, x - 60 * i, y);
		if (n % 10 == 8)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_8, x - 60 * i, y);
		if (n % 10 == 9)
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_9, x - 60 * i, y);
		n /= 10;
		i ++;
	}
	if (n == 0 && i == 1)
		mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_0, x - 60 * i, y);
}


static void	put_sprite(t_game *g, int tx, int ty, int x, int y)
{
	int	x_pix;
	int	y_pix;
	char c;
	
	x_pix = x * PIX - (g->p_x % PIX);
	y_pix = y * PIX - (g->p_y % PIX);
	c = g->mod_map[ty + y][tx + x];
	if (c == '1' && (g->mod_map[ty + y - 1][tx + x] == '0' || g->mod_map[ty + y - 1][tx + x] == 'W'))
		mlx_put_image_to_window(g->mlx, g->win_ptr, g->grass, x_pix, y_pix);
	else if (c == '1')
		mlx_put_image_to_window(g->mlx, g->win_ptr, g->floor, x_pix, y_pix);
	if (c == 'W')
	{
		if (g->mod_map[ty + y - 1][tx + x] == '0')
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->wall_top, x_pix, y_pix);
		else if (g->mod_map[ty + y + 1][tx + x] == '0')
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->wall_bot, x_pix, y_pix);
		else
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->wall, x_pix, y_pix);
	}
	if (c == '0')
		mlx_put_image_to_window(g->mlx, g->win_ptr, g->sky, x_pix, y_pix);
}

void	draw_map(t_game *g)
{
	int		y;
	int		x;
	int		ty;
	int		tx;

	ty = g->p_y / PIX - (HEIGHT + 5) / 2;
	tx = g->p_x / PIX - WIDTH / 2;
	if (tx >= 20)
	{
		g->score ++;
		g->vel += (g->vel < 25 && g->score % 2 == 0);
		g->p_x = 1000;
		split_free(g->mod_map);
		g->mod_map = create_walls(g);
	}
	y = -1;
	while (y <= HEIGHT)
	{
		x = -1;
		while (x <= WIDTH)
		{
			put_sprite(g, tx, ty, x, y);
			x ++;
		}
		mlx_put_image_to_window(g->mlx, g->win_ptr, g->player, (WIDTH / 2 - 4) * PIX + 20, (HEIGHT + 5) / 2 * PIX + 20);
		put_score(g, g->top_score, WIDTH * PIX, 0);
		put_score(g, g->score, WIDTH * PIX, 110);
		y ++;
	}
}

/*
mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_0, 100, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_1, 160, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_2, 220, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_3, 280, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_4, 340, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_5, 400, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_6, 460, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_7, 520, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_8, 580, 100);
			mlx_put_image_to_window(g->mlx, g->win_ptr, g->num_9, 640, 100);
*/
