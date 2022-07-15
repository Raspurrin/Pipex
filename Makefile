# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 18:53:57 by mialbert          #+#    #+#              #
#    Updated: 2022/07/15 20:39:37 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= clang
NAME	= pipex
CFLAGS	= -Wall -Werror -Wextra
HEADER	= -I includes -I libs/libft/srcs
LIBFT	= ./libs/libft/
#DEBUG	= -fsanitize=address
SRCS	=	./srcs/init.c \
			./srcs/errors.c \
			./srcs/execution.c \
			./srcs/inout_files.c

OBJS	= $(SRCS:.c=.o)

NC		:= \033[0m
B_RED	:= \033[1;31m
RED 	:= \033[0;31m
GREEN 	:= \033[0;32m
BLUE 	:= \033[0;34m
PURPLE	:= \033[0;35m

SUBM_STATE := $(shell find libs/libft -type f)

# to automatically initialize the submodules
ifeq ($(SUBM_STATE),)
SUBM_FLAG	= submodule
else 
SUBM_FLAG	= 
endif

all: $(SUBM_STATE) libft $(NAME)

# %.o : %.c 
# 	%(CC) $(CFLAGS) -c $< -o $@

submodule: 
	git submodule init 
	git submodule update

libft:
	@echo "\n${BLUE}======== libft ========${NC}"
	@$(MAKE) -C $(LIBFT)

$(NAME): $(SRCS)
	@echo "${PURPLE}======== Compiling ========${NC}"
	$(CC) $(HEADER) -L$(LIBFT) $(SRCS) $(DEBUG) -lft -o $(NAME)

bonus: $(OBJS)
	@echo "${PURPLE}======== Bonus... ========${NC}"
	$(CC) -D BONUS=1 $(HEADER) -L$(LIBFT) $(SRCS) $(DEBUG) -lft -o $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "${B_RED}Cleaning: ${RED} $(OBJS)"
	@$(MAKE) -C $(LIBFT) fclean

fclean: clean
	@rm -f $(NAME)
	@echo "${B_RED}Cleaning: ${RED} $(NAME)"

re: fclean all

.PHONY: all, libft, clean, fclean
