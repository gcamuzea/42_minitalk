/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 02:34:14 by gucamuze          #+#    #+#             */
/*   Updated: 2021/07/27 19:06:27 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

static t_server_globals	g_server;

void	add_to_buff(char c)
{
	int	n;

	n = 0;
	while (g_server.buffer[n])
		n++;
	g_server.buffer[n] = c;
	if (n == 511 || c == 0)
	{
		putstr(g_server.buffer);
		write(1, "\n", 1);
		while (n >= 0)
			g_server.buffer[n--] = 0;
		while (n < 9)
			g_server.binary[n++] = 0;
	}
}

void	get_char_from_binary(void)
{
	int		n;
	char	c;

	c = 0;
	c += (g_server.binary[7] - 48) * 128;
	c += (g_server.binary[6] - 48) * 64;
	c += (g_server.binary[5] - 48) * 32;
	c += (g_server.binary[4] - 48) * 16;
	c += (g_server.binary[3] - 48) * 8;
	c += (g_server.binary[2] - 48) * 4;
	c += (g_server.binary[1] - 48) * 2;
	c += (g_server.binary[0] - 48) * 1;
	add_to_buff(c);
	n = 0;
	while (n < 9)
		g_server.binary[n++] = 0;
}

void	fill_binary(char c)
{
	int	n;

	n = 0;
	while (g_server.binary[n] && n < 9)
		n++;
	g_server.binary[n] = c;
	if (n >= 7)
		get_char_from_binary();
}

void	sigusr_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid)
	{
		g_server.client_id = info->si_pid;
		if (sig == SIGUSR1)
			fill_binary('1');
		else
			fill_binary('0');
		kill(info->si_pid, SIGUSR1);
	}
	else
		kill(g_server.client_id, SIGUSR2);
}

int	main(int ac, char **av)
{
	pid_t				pid;
	struct sigaction	sigusr_sigaction;

	(void)av;
	if (ac > 1)
		putstr("Server does not need arguments and will not use them\n");
	sigusr_sigaction.sa_sigaction = &sigusr_handler;
	sigemptyset(&sigusr_sigaction.sa_mask);
	sigaddset(&sigusr_sigaction.sa_mask, SIGUSR1);
	sigaddset(&sigusr_sigaction.sa_mask, SIGUSR2);
	sigusr_sigaction.sa_flags = SA_SIGINFO;
	pid = 0;
	while ((int)pid < 9)
		g_server.binary[pid++] = 0;
	pid = 0;
	while ((int)pid < 513)
		g_server.buffer[pid++] = 0;
	pid = getpid();
	putstr("Server online, PID is : ");
	putnbr((unsigned int)pid);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sigusr_sigaction, NULL);
	sigaction(SIGUSR2, &sigusr_sigaction, NULL);
	while (1)
		;
}
