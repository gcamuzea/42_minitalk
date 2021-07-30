/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 02:35:16 by gucamuze          #+#    #+#             */
/*   Updated: 2021/07/27 20:12:48 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	ft_strlen(char *str)
{
	int	strlen;

	strlen = 0;
	while (*str++)
		strlen++;
	return (strlen);
}

void	putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

int	is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	putnbr(int n)
{
	char	c;

	if (n < 10)
	{
		c = n + 48;
		write(1, &c, 1);
	}
	else
	{
		putnbr(n / 10);
		c = n % 10 + 48;
		write(1, &c, 1);
	}
}
