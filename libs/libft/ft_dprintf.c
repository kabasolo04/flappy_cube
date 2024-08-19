/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kabasolo <kabasolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:44:11 by kabasolo          #+#    #+#             */
/*   Updated: 2024/05/24 19:06:26 by kabasolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define NUM "0123456789"
#define HEX1 "0123456789abcdef"
#define HEX2 "0123456789ABCDEF"

static int	ft_dec(int fd, long int nbr, char *base)
{
	if (nbr < 0)
		return (write(fd, "-", 1) + ft_dec(fd, nbr * (-1), base));
	if (nbr > 9)
		return (ft_dec(fd, nbr / 10, base) + write(fd, &base[nbr % 10], 1));
	return (write(fd, &base[nbr % 10], 1));
}

static int	ft_hex(int fd, unsigned long nbr, char *base)
{
	if (nbr > 15)
		return (ft_hex(fd, nbr / 16, base) + write(fd, &base[nbr % 16], 1));
	return (write(fd, &base[nbr % 16], 1));
}

static int	ft_str(int fd, char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (ft_str(fd, "(null)"));
	while (str[i])
		write(fd, &str[i++], 1);
	return (i);
}

static int	ft_conversor(int fd, char c, va_list va)
{
	if (c == 'c')
		return (write(fd, &(char){va_arg(va, int)}, 1));
	if (c == 's')
		return (ft_str(fd, va_arg(va, char *)));
	if (c == 'p')
	{
		write(fd, "0x", 2);
		return (2 + ft_hex(fd, va_arg(va, unsigned long), HEX1));
	}
	if (c == 'd' || c == 'i')
		return (ft_dec(fd, va_arg(va, int), NUM));
	if (c == 'u')
		return (ft_dec(fd, va_arg(va, unsigned int), NUM));
	if (c == 'x')
		return (ft_hex(fd, va_arg(va, unsigned int), HEX1));
	if (c == 'X')
		return (ft_hex(fd, va_arg(va, unsigned int), HEX2));
	return (write(fd, &c, 1));
}

int	ft_dprintf(int fd, char const *s, ...)
{
	int		n;
	va_list	va;

	n = 0;
	va_start(va, s);
	while (*s)
	{
		if (*s == '%')
			n += ft_conversor(fd, *++s, va);
		else
			n += write(fd, s, 1);
		s += !(!*s);
	}
	va_end(va);
	return (n);
}
