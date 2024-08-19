/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 14:02:46 by kabasolo          #+#    #+#             */
/*   Updated: 2024/07/09 16:50:06 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		l;
	char	*str;

	l = 0;
	i = 0;
	while (s1 && s1[l])
		l ++;
	str = (char *)malloc(sizeof(char) * (l + 1));
	if (str)
	{
		while (i < l)
		{
			str[i] = s1[i];
			i ++;
		}
		str[i] = '\0';
		return (str);
	}
	return (NULL);
}
