/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 17:05:20 by gucamuze          #+#    #+#             */
/*   Updated: 2021/07/27 20:10:12 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	custom_atoi(char *str, pid_t *srv_pid)
{
	int	number;

	number = 0;
	while (*str)
	{
		if (!is_numeric(*str))
			return (0);
		number = (number * 10) + (*str - 48);
		str++;
	}
	if (number != 0)
	{
		*srv_pid = (pid_t)number;
		return (1);
	}
	return (0);
}

t_parsed_args	*parse_args(char **av)
{
	t_parsed_args	*args;

	args = malloc(sizeof(t_parsed_args));
	if (!args)
		return (NULL);
	if (!custom_atoi(av[1], &args->srv_pid))
		return (NULL);
	args->string = av[2];
	args->string_len = ft_strlen(av[2]);
	return (args);
}

char	*get_binary(char c)
{
	char	*binary;
	int		n;

	binary = malloc(9 * sizeof(char));
	if (!binary)
		return (NULL);
	n = 0;
	while (n < 8)
	{
		binary[n++] = c % 2 + 48;
		c /= 2;
	}
	binary[8] = 0;
	return (&binary[0]);
}

char	**create_list(t_parsed_args *args)
{
	char	**list;
	int		n;

	list = malloc((args->string_len + 1) * sizeof(char *));
	if (!list)
		return (NULL);
	n = -1;
	while (++n <= args->string_len)
		list[n] = get_binary(args->string[n]);
	return (list);
}

void	set_variables(t_client_globals *global, t_parsed_args *args)
{
	global->list = create_list(args);
	global->bytes_to_send = 8 * (args->string_len + 1);
	global->server_pid = args->srv_pid;
	global->bytes_sent = 0;
	global->loop = 1;
}
