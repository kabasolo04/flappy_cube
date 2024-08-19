/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 11:39:44 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/06 18:09:56 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*mod_join(char *cat, char *tail)
{
	char *res;

	res = ft_strjoin(cat, tail);
	free(cat);
	return (res);
}

static char	**get_map(int fd)
{
	int		bytes;
	char	*map;
	char	str[2];
	char	**result;

	str[1] = '\0';
	bytes = read(fd, str, 1);
	map = ft_strdup("");
	while (bytes > 0)
	{
		map = mod_join(map, str);
		if (str[0] == '\n' && map[ft_strlen(map)] == '\n')
			return (free(map), error("Only one '\\n' per line please."), NULL);
		bytes = read(fd, str, 1);
	}
	if (map[0] == '\0')
		return (free(map), error("Map lecture went wrong."), NULL);
	result = ft_split(map, '\n');
	free(map);
	return (result);
}

static void	get_pos(t_game *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			if (data->map[y][x] == 'P')
			{
				data->p_x = x;
				data->p_y = y;
			}
			x ++;
		}
		y ++;
	}
}

int	get_data(t_game *data, int fd)
{
	data->map = get_map(fd);
	if (!data->map)
		return (1);
	data->col = ft_strlen(data->map[0]);
	data->lines = 0;
	while (data->map[data->lines])
		data->lines ++;
	data->p = find(data->map, 'P');
	if (data->p != 1)
		return (split_free(data->map), error("Non-valid player quantity."));
	get_pos(data);
	data->map[data->p_y][data->p_x] = '0';
	return (0);
}
