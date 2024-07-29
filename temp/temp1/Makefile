# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 16:18:50 by dde-maga          #+#    #+#              #
#    Updated: 2024/05/09 17:13:03 by dde-maga         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex 

LIB_SRCS =  ft_strlen.c ft_putchar_fd.c ft_putstr_fd.c ft_memset.c \
			ft_calloc.c ft_strdup.c ft_itoa.c ft_split.c \
			ft_strncmp.c ft_substr.c ft_strjoin.c ft_strcmp.c ft_isspace.c
SRC_GNL =	gnl_utils.c gnl.c
SRC_PARSER = arguments.c files.c here_doc.c
SRC_PROCESSES = childs.c
SRC_CLEANING = errors.c

SRC =	$(addprefix ./srcs/lib/, $(LIB_SRCS)) \
		$(addprefix ./srcs/lib/gnl/, $(SRC_GNL))\
		$(addprefix ./srcs/parser/, $(SRC_PARSER))\
		$(addprefix ./srcs/processes/, $(SRC_PROCESSES))\
		$(addprefix ./srcs/cleaning/, $(SRC_CLEANING))\

SRCOBJ = obj/
CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJ = $(addprefix $(SRCOBJ), $(SRC:./srcs/%.c=%.o))

all: $(NAME)


$(SRCOBJ)%.o: srcs/%.c
	@mkdir -p $(SRCOBJ)
	@mkdir -p $(dir $@)
	@${CC} ${CFLAGS} -c $< -o $@
	
$(NAME): $(OBJ)
	@${CC} ${CFLAGS} main.c ${OBJ} -o $(NAME)
	@echo Done Pipex!

clean:
	@rm -rf $(SRCOBJ)

fclean: clean
	@rm -rf $(NAME)
	@echo Cleaned Pipex!

re: fclean all

