/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:47:03 by kabasolo          #+#    #+#             */
/*   Updated: 2024/08/02 12:55:46 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	split_free(char **splited)
{
	int	i;

	i = 0;
	if (!splited)
		return ;
	while (splited[i])
		free(splited[i++]);
	free(splited);
}
