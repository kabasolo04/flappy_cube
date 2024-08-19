/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:42:38 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/05 18:45:59 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**split_cpy(char **splited)
{
	int		i;
	int		t;
	char	**cpy;

	i = split_len(splited);
	cpy = (char **)malloc((i + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	i = 0;
	while (splited[i])
	{
		cpy[i] = (char *)malloc((ft_strlen(splited[i]) + 1) * sizeof(char ));
		if (!cpy[i])
			return (split_free(cpy), NULL);
		t = 0;
		while (splited[i][t])
		{
			cpy[i][t] = splited[i][t];
			t ++;
		}
		cpy[i][t] = '\0';
		i ++;
	}
	cpy[i] = NULL;
	return (cpy);
}
