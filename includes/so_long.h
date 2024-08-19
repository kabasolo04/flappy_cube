/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:00:52 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/09 13:31:56 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <fcntl.h>
# include <time.h>

# define ESC 65307
# define SPACE 32

# define PIX 100
# define HEIGHT 15
# define WIDTH 13

typedef struct s_game
{
	int		map_fd;
	int		score_fd;
	
	char	**map;
	char	**mod_map;
	
	void	*mlx;
	void	*win_ptr;

	void	*floor;
	void	*grass;
	void	*sky;
	void	*wall;
	void	*wall_bot;
	void	*wall_top;
	void	*player;
	void	*player0;
	void	*player1;
	void	*player2;
	void	*num_0;
	void	*num_1;
	void	*num_2;
	void	*num_3;
	void	*num_4;
	void	*num_5;
	void	*num_6;
	void	*num_7;
	void	*num_8;
	void	*num_9;

	int		hor;
	int		ver;
	int		vel;
	int		score;
	int		top_score;
	
	int		col;
	int		lines;

	size_t	p;

	int		p_x;
	int		p_y;
}	t_game;

void	press_hook(int key, t_game *g);
int		get_data(t_game *data, int fd);
int		error(char *ms);
char	**map_cpy(t_game *data);
char	**create_walls(t_game *g);
int		find(char **map, char c);
char	*mod_join(char *cat, char *tail);
void	ft_close(t_game *game);
void	draw_map(t_game *g);

#endif //SO_LONG_BONUS_H