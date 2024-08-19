/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 19:41:45 by kabasolo          #+#    #+#             */
/*   Updated: 2024/04/11 13:53:14 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long	res;
	int		b;

	while (ft_isspace(*str))
		str++;
	b = 1;
	if (*str == '-')
		b = -1;
	str += (*str == '+' || *str == '-');
	res = 0;
	while (ft_isdigit(*str))
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (b * res);
}
