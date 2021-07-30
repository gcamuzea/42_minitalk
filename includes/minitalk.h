/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 02:15:31 by gucamuze          #+#    #+#             */
/*   Updated: 2021/07/27 19:31:17 by gucamuze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_parsed_args
{
	char		*string;
	int			string_len;
	pid_t		srv_pid;
}				t_parsed_args;

typedef struct s_client_globals
{
	char			**list;
	int				bytes_sent;
	int				bytes_to_send;
	volatile int	loop;
	pid_t			server_pid;
}				t_client_globals;

typedef struct s_server_globals
{
	char	binary[9];
	char	buffer[513];
	pid_t	client_id;
}			t_server_globals;

int				ft_strlen(char *str);
void			putstr(char *str);
void			putnbr(int n);
int				is_numeric(char c);
int				custom_atoi(char *str, pid_t *srv_pid);
t_parsed_args	*parse_args(char **av);
char			*get_binary(char c);
void			set_variables(t_client_globals *global, t_parsed_args *args);

#endif