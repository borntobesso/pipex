# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sojung <sojung@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/08 15:16:05 by sojung            #+#    #+#              #
#    Updated: 2022/02/22 13:10:59 by sojung           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

BONUS = .

SRC = $(addprefix src/,main.c utils.c error.c pipex.c parsing.c \
check_parsing.c ft_split.c child.c)

BSRC = $(addprefix bsrc/,main_bonus.c utils_bonus.c error_bonus.c \
pipex_bonus.c parsing_bonus.c check_parsing_bonus.c ft_split_bonus.c \
here_doc.c multiple_pipes.c get_next_line.c get_next_line_utils.c)

OBJ = $(SRC:.c=.o)

BOBJ = $(BSRC:.c=.o)

INCLUDE = include/

CC = clang

FLAGS = -Wall -Wextra -Werror

%.o : %.c $(INCLUDE)
	$(CC) $(FLAGS) -c $< -o $@ -I $(INCLUDE)

all : $(NAME)

bonus : $(BONUS)

$(OBJ) : $(INCLUDE)pipex.h

$(BOBJ) : $(INCLUDE)pipex_bonus.h

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) -o $@ $^

$(BONUS) : $(BOBJ)
	$(CC) $(FLAGS) -o $(NAME) $^

clean :
	rm -f $(OBJ) $(BOBJ)

fclean : clean
	rm -f $(NAME)

re : fclean all
