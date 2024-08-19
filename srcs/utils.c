/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 13:13:34 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/06 19:24:15 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	error(char *ms)
{
	write(2, "\nERROR: ", 8);
	write(2, ms, ft_strlen(ms));
	write(2, "\n\n", 2);
	return (1);
}

int	find(char **map, char c)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == c)
				i ++;
			x ++;
		}
		y ++;
	}
	return (i);
}

void	ft_close(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win_ptr);
	mlx_destroy_image(game->mlx, game->wall_top);
	mlx_destroy_image(game->mlx, game->wall_bot);
	mlx_destroy_image(game->mlx, game->player);
	mlx_destroy_image(game->mlx, game->floor);
	mlx_destroy_image(game->mlx, game->grass);
	mlx_destroy_image(game->mlx, game->wall);
	mlx_destroy_image(game->mlx, game->sky);
	mlx_destroy_image(game->mlx, game->num_0);
	mlx_destroy_image(game->mlx, game->num_1);
	mlx_destroy_image(game->mlx, game->num_2);
	mlx_destroy_image(game->mlx, game->num_3);
	mlx_destroy_image(game->mlx, game->num_4);
	mlx_destroy_image(game->mlx, game->num_5);
	mlx_destroy_image(game->mlx, game->num_6);
	mlx_destroy_image(game->mlx, game->num_7);
	mlx_destroy_image(game->mlx, game->num_8);
	mlx_destroy_image(game->mlx, game->num_9);
	free (game->mlx);
	split_free(game->map);
	split_free(game->mod_map);
	close(game->map_fd);
	close(game->score_fd);
	exit(0);
}
