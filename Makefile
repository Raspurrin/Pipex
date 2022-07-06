# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 18:53:57 by mialbert          #+#    #+#              #
#    Updated: 2022/07/06 00:18:04 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= clang
NAME	= pipex
CFLAGS	= -Wall -Werror -Wextra
HEADER	= -I includes -I libs/libft/srcs
LIBFT	= ./libs/libft/srcs/
DEBUG	= 
SRCS	=	./srcs/init.c \
			./srcs/errors.c \
			./srcs/execution.c

OBJS	= $(SRCS:.c=.o)

NC		:= \033[0m
RED 	:= \033[1;31m
GREEN 	:= \033[0;32m
BLUE 	:= \033[0;34m
PURPLE	:= \033[0;35m

all: libft $(NAME)

libft:
	@echo "\n${BLUE}======== libft ========${NC}"
	@$(MAKE) -C $(LIBFT)

$(NAME): $(OBJS)
	@echo "${PURPLE}======== Compiling... ========${NC}"
	$(CC) -g $(CFLAGS) $(HEADER) $(LIBFT)libft.a $(OBJS) $(DEBUG) -o $(NAME)
# $(CC) $(CFLAGS) $(HEADER) $(OBJS) libs/libft/srcs/libft.a -o $(NAME)

# clang -Wall -Werror -Wextra -I includes -I libs/libft/srcs  ./srcs/init.o ./srcs/errors.o ./srcs/execution.o libs/libft/srcs/libft.a -o pipex
clean:
	@rm -f $(OBJS)
	@echo "${RED} Removed ${NC} $(OBJS)"
	@$(MAKE) -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@echo "${RED} Removed ${NC} $(NAME)"
	@$(MAKE) -C $(LIBFT) fclean

re: fclean all

.PHONY: all, libft, clean, fclean
