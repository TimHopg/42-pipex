# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thopgood <thopgood@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/10 11:25:34 by thopgood          #+#    #+#              #
#    Updated: 2024/08/02 21:31:45 by thopgood         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= pipex

CC 			= cc
RM 			= rm -rf
INCLUDE 	= -Iinclude

CFLAGS = -Wall -Wextra -Werror $(INCLUDE) -g -O0 # -fsanitize=address

SRC_DIR 	= src/
OBJ_DIR 	= obj/
LIBFT_DIR 	= libft/
LIBFT		= -L $(LIBFT_DIR) -lft

SRC 		= 	pipex.c \
				core_logic.c \
				core_logic2.c \
				parse_args.c \
				parse_args2.c \
				parse_args3.c \
				files.c \
				error.c \
				pipex_utils.c

OBJ 		= 	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	@echo ""${BLUE}$(NAME)""${NC}Compiling... "\c"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo ""${GREEN}Complete""$(NC)""

clean:
	@cd $(LIBFT_DIR) && $(MAKE) clean
	@echo ""${BLUE}$(NAME)""${NC}Cleaning..."\c"
	@$(RM) $(OBJ_DIR)
	@echo ""${GREEN}Complete""$(NC)""

fclean: clean
	@cd $(LIBFT_DIR) && $(MAKE) fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

# Colours
WHITE	=	'\033[0;37m'
YELLOW	=	'\033[0;33m'
BLUE	=	'\033[0;34m'
GREEN	=	'\033[0;32m'
RED		=	'\033[0;31m'
NC		=	'\033[0m' # no colour
#> /dev/null