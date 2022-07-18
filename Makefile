# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bahaas <bahaas@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 15:07:09 by bahaas            #+#    #+#              #
#    Updated: 2022/06/22 18:25:59 by bahaas           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= ft_project

SRCS			= $(wildcard srcs/*.c)\

CC				= clang

#CFLAGS			= -Wextra -Werror -Wall -g
CFLAGS			= -g

HEADER			= -I /includes

OBJS			= ${SRCS:.c=.o}

.c.o:
	@printf "\033[34m[FT_PROJECT]\033[0m Generating .o files: \033[32mOK\033[0m%-33.33s\r\033[0m"
			@${CC} ${CFLAGS} ${HEADER} -c $< -o ${<:.c=.o}

all: 		${NAME}

ft_project: 	${OBJS}
			@printf "\n"
			@make -C libft/ --no-print-directory -s
			@${CC} ${CFLAGS} ${HEADER} ${OBJS} -o ${NAME} -L libft/ -lft -lm
			@echo "\033[34m[FT_PROJECT]\033[0m Building ft_project program : \033[32mOK\033[0m"

clean:
			@make clean -C libft/ --no-print-directory
			@rm -rf ${OBJS}
			@echo "\033[34m[FT_PROJECT]\033[0m Delete .o files : \033[32mOK\033[0m"

fclean:		clean
			@make fclean -C libft/ --no-print-directory
			@rm -rf ${NAME}
			@echo "\033[34m[FT_PROJECT]\033[0m Delete executable files : \033[32mOK\033[0m"

re: 		fclean all

.PHONY:	all clean fclean re
