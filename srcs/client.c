/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 02:15:36 by gucamuze          #+#    #+#             */
/*   Updated: 2021/07/30 12:15:31 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_client_globals	g_client;

void	free_all(int string_len, t_parsed_args *args)
{
	int	n;

	n = -1;
	while (++n <= string_len)
		free(g_client.list[n]);
	free(g_client.list);
	free(args);
}

int	send_byte(void)
{
	char	byte;
	int		char_index;
	int		byte_index;
	int		ret;

	char_index = g_client.bytes_sent / 8;
	byte_index = g_client.bytes_sent % 8;
	byte = g_client.list[g_client.bytes_sent / 8][g_client.bytes_sent % 8];
	if (byte == '1')
		ret = kill(g_client.server_pid, SIGUSR1);
	else
		ret = kill(g_client.server_pid, SIGUSR2);
	g_client.bytes_sent++;
	return (ret);
}

void	sigusr1_client_handler(int sig)
{
	if (sig == SIGUSR1)
	{
		if (g_client.bytes_sent < g_client.bytes_to_send)
			send_byte();
		else if (g_client.bytes_sent == g_client.bytes_to_send)
		{
			putstr("Message fully received and displayed by the server !\n");
			g_client.loop = 0;
		}
	}
	else
	{
		g_client.bytes_sent--;
		send_byte();
	}
}

void	set_sigaction(struct sigaction *sigusr_sigaction)
{
	sigusr_sigaction->sa_handler = &sigusr1_client_handler;
	sigusr_sigaction->sa_flags = 0;
	sigemptyset(&sigusr_sigaction->sa_mask);
	sigaddset(&sigusr_sigaction->sa_mask, SIGUSR1);
	sigaddset(&sigusr_sigaction->sa_mask, SIGUSR2);
	sigaction(SIGUSR1, sigusr_sigaction, NULL);
	sigaction(SIGUSR2, sigusr_sigaction, NULL);
}

int	main(int ac, char **av)
{
	t_parsed_args		*args;
	struct sigaction	sigusr_sigaction;
	int					check_server;

	if (ac == 3)
	{
		args = parse_args(av);
		if (args)
		{
			set_sigaction(&sigusr_sigaction);
			set_variables(&g_client, args);
			check_server = send_byte();
			if (check_server == -1)
				putstr("Error : incorrect server PID !\n");
			else
				while (g_client.loop)
					;
			free_all(args->string_len, args);
		}
		else
			putstr("Error: usually comes from provided server PID.\n");
	}
	else
		putstr("Error : usage = ./client [SERVER PID] [STRING TO SEND]");
}
