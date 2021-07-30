# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gucamuze <gucamuze@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/15 02:21:09 by gucamuze          #+#    #+#              #
#    Updated: 2021/07/27 19:45:47 by gucamuze         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER	= server
CLIENT	= client
CC		= clang -Wall -Wextra -Werror
FLAGS	= -O3
RM		= rm -f

SRCS			=	./srcs
SRV_FILES		= 	${SRCS}/server.c ${SRCS}/utils.c
CLIENT_FILES	=	${SRCS}/client.c ${SRCS}/utils.c ${SRCS}/client_utils.c

SERVER_OFILES	= 	${SRV_FILES:.c=.o}
CLIENT_OFILES	= 	${CLIENT_FILES:.c=.o}

.c.o:
				${CC} ${FLAGS} -c $< -o ${<:.c=.o}

all:		${SERVER} ${CLIENT}

${SERVER}:	${SERVER_OFILES}
				${CC} ${FLAGS} ${SERVER_OFILES} -o server

${CLIENT}:	${CLIENT_OFILES}
				${CC} ${FLAGS} ${CLIENT_OFILES} -o client

clean:
				${RM} ${CLIENT_OFILES} ${SERVER_OFILES}

fclean:		clean
				${RM} ${SERVER} ${CLIENT}

re:			fclean all


.PHONY:	all clean fclean re bonus server client