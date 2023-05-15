# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 16:01:04 by ddyankov          #+#    #+#              #
#    Updated: 2023/05/15 17:45:28 by ddyankov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c utils.c one_philo.c routine.c routine_utils.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g -pthread

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $(OBJ) -o $(NAME)
        
clean:
	@rm -f $(OBJ) 

fclean:clean
	@rm -f $(NAME)
        
re: fclean all

.PHONY:         all clean fclean re

