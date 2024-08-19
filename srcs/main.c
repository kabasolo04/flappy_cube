/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:55:26 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/13 16:40:17 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	load_sprites(t_game *g, int x, int y)
{
	g->sky = mlx_xpm_file_to_image(g->mlx, "textures/sky.xpm", &x, &y);
	g->wall = mlx_xpm_file_to_image(g->mlx, "textures/wall.xpm", &x, &y);
	g->grass = mlx_xpm_file_to_image(g->mlx, "textures/grass.xpm", &x, &y);
	g->floor = mlx_xpm_file_to_image(g->mlx, "textures/floor.xpm", &x, &y);
	g->player0 = mlx_xpm_file_to_image(g->mlx, "textures/player.xpm", &x, &y);
	g->player1 = mlx_xpm_file_to_image(g->mlx, "textures/P/player1.xpm", &x, &y);
	g->player2 = mlx_xpm_file_to_image(g->mlx, "textures/P/player2.xpm", &x, &y);
	g->wall_bot = mlx_xpm_file_to_image(g->mlx, "textures/wall_bot.xpm", &x, &y);
	g->wall_top = mlx_xpm_file_to_image(g->mlx, "textures/wall_top.xpm", &x, &y);
	g->num_0 = mlx_xpm_file_to_image(g->mlx, "textures/N/0.xpm", &x, &y);
	g->num_1 = mlx_xpm_file_to_image(g->mlx, "textures/N/1.xpm", &x, &y);
	g->num_2 = mlx_xpm_file_to_image(g->mlx, "textures/N/2.xpm", &x, &y);
	g->num_3 = mlx_xpm_file_to_image(g->mlx, "textures/N/3.xpm", &x, &y);
	g->num_4 = mlx_xpm_file_to_image(g->mlx, "textures/N/4.xpm", &x, &y);
	g->num_5 = mlx_xpm_file_to_image(g->mlx, "textures/N/5.xpm", &x, &y);
	g->num_6 = mlx_xpm_file_to_image(g->mlx, "textures/N/6.xpm", &x, &y);
	g->num_7 = mlx_xpm_file_to_image(g->mlx, "textures/N/7.xpm", &x, &y);
	g->num_8 = mlx_xpm_file_to_image(g->mlx, "textures/N/8.xpm", &x, &y);
	g->num_9 = mlx_xpm_file_to_image(g->mlx, "textures/N/9.xpm", &x, &y);
	if (!(g->sky && g->wall && g->wall_top && g->floor && g->player0 && g->player1 && g->player2))
		return (0);
	if (!(g->num_0 && g->num_1 && g->num_2 && g->num_3 && g->num_4))
		return (0);
	if (!(g->num_5 && g->num_6 && g->num_7 && g->num_8 && g->num_9))
		return (0);
	return (1);
}

void	animation(t_game *g)
{
	char *num;
	
	g->p_x += g->vel;
	g->p_y -= g->ver;
	if (g->ver != -15)
		g->ver -= 2;
	if (g->map[(g->p_y + 80) / PIX][g->p_x / PIX] == '1')
		g->ver = 30;
	g->player = g->player0;
	/*
	if (g->ver >= 20 && g->map[(g->p_y + 180) / PIX][g->p_x / PIX] == '1')
		g->player = g->player1;
	*/
	if (g->score > g->top_score)
	{
		g->top_score = g->score;
		num = ft_itoa(g->top_score);
		close(g->score_fd);
		g->score_fd = open("data/top_score", O_RDWR | O_TRUNC);
		ft_dprintf(g->score_fd, "%s", num);
		free(num);
	}
	if (g->mod_map[g->p_y / PIX + ((g->p_y % PIX) > 50 - g->ver)][(g->p_x - 340) / PIX] == 'W')
	{
		usleep(120000);
		g->ver = -10;
		g->vel = 15;
		g->p_y = (g->lines - 11) * PIX;
		g->p_x = 900;
		g->score = 0;
		split_free(g->mod_map);
		g->mod_map = create_walls(g);
	}
	draw_map(g);
	usleep(15000);
}

static void	start_game(t_game	*game)
{
	srand(time(NULL));
	game->mod_map = create_walls(game);
	game->mlx = mlx_init();
	game->p_x *= PIX;
	game->p_y *= PIX;
	game->hor = 0;
	game->ver = -10;
	game->vel = 15;
	game->score = 0;
	game->win_ptr = mlx_new_window (game->mlx, WIDTH * PIX, HEIGHT * PIX, "SO_LONG_BONUS");
	if (!load_sprites(game, 0, 0))
		return (error("Could not open textures."), exit(0));
	mlx_loop_hook(game->mlx, (void *)animation, game);
	mlx_hook(game->win_ptr, 17, 0, (void *)ft_close, game);
	mlx_hook(game->win_ptr, 2, 1L << 0, (void *)press_hook, game);
	mlx_loop (game->mlx);
}

static int	get_score(int fd)
{
	int		bytes;
	char	*line;
	char	buf[2];

	buf[1] = '\0';
	bytes = read(fd, buf, 1);
	line = ft_strdup("");
	while(bytes > 0)
	{
		line = mod_join(line, buf);
		bytes = read(fd, buf, 1);
	}
	bytes = ft_atoi(line);
	return (free(line), bytes);
}

int	main()
{
	t_game	game;

	game.map_fd = open("data/bird.ber", O_RDONLY);
	game.score_fd = open("data/top_score", O_RDONLY);
	if (game.map_fd < 0 || game.score_fd < 0)
		return (error("Data files."));
	game.top_score = get_score(game.score_fd);
	if (get_data(&game, game.map_fd) != 0)
		return (1);
	start_game(&game);
	return (0);
}

/*

	px_pos = (g->p_x + 40 * g->hor) / PIX + ((g->p_x + 40 * g->hor) % PIX >= 50);
	py_pos = (g->p_y + 40 * g->ver) / PIX + ((g->p_y + 40 * g->ver) % PIX >= 50);

------------------------------------------------------------------------------

		b = (b + 1) * (b <= n) + i * (b > n); //Legal

		b = (b <= n ? b + 1 : i); //Prohibido (Ternario)

	EJEMPLO: (i -> i + 1 -> i + 2 -> i + 3 -> ... -> n -> i -> i + 1 -> ...)

------------------------------------------------------------------------------

		n = a * (n == b) + b * (n == a); //Legal

		n = (n == a ? n = b : n = a); //Prohibido (Ternario)

	EJEMPLO: (a -> b -> a -> b -> a -> b -> ...)

------------------------------------------------------------------------------

		n = a * (n == b) + b * (n == c) + c * (n == a);

	EJEMPLO: (a -> b -> c -> a -> b -> c -> ...)

------------------------------------------------------------------------------
*/

