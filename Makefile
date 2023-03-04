# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mialbert <mialbert@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 18:53:57 by mialbert          #+#    #+#              #
#    Updated: 2023/03/04 23:45:33 by mialbert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= clang
NAME	= pipex
CFLAGS	= -Wall -Werror -Wextra
HEADER	= -I includes -I libs/libft/srcs
LIBFT	= ./libs/libft/
LIBFT_A = libs/libft/libft.a # ??
DEBUG	= -fsanitize=address
SRCS	=	./srcs/init.c \
			./srcs/errors.c \
			./srcs/execution.c \
			./srcs/inout_files.c \
			./srcs/main.c

OBJS	= $(SRCS:.c=.o)

NC			:= \033[0m
B_RED		:= \033[1;31m
RED 		:= \033[0;31m
B_GREEN		:= \033[1;32m
GREEN 		:= \033[0;32m
B_BLUE 		:= \033[1;34m
BLUE 		:= \033[0;34m
PURPLE		:= \033[0;35m
B_PURPLE	:= \033[1;35m

SUBM_STATE := $(shell find libs/libft -type f)

# to automatically initialize the submodules
ifeq ($(SUBM_STATE),)
SUBM_FLAG	= submodule
else 
SUBM_FLAG	= 
endif

all: $(SUBM_FLAG) $(LIBFT_A) $(NAME) 

%.o : %.c 
	@echo "$(B_BLUE)Compiling: $(BLUE)$(notdir $<) 🔨$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

submodule: 
	git submodule init 
	git submodule update

$(LIBFT_A):
	@echo "\n${BLUE}======== libft ========${NC}"
	@$(MAKE) -C $(LIBFT)

Pipex: 
	@echo "${PURPLE}======== Pipex ========${NC}"

$(NAME): Pipex $(OBJS)
	@$(CC) $(HEADER) -L$(LIBFT) $(SRCS) $(DEBUG) -lft -o $(NAME)

bonus: $(LIBFT_A) $(OBJS)
	@echo "${PURPLE}======== Bonus... ========${NC}"
	$(CC) -D BONUS=1 $(HEADER) -L$(LIBFT) $(SRCS) $(DEBUG) -lft -o $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "${B_RED}🧹 Cleaning: ${RED} $(notdir $(OBJS))"
	@$(MAKE) -C $(LIBFT) fclean

fclean: clean
	@rm -f $(NAME)
	@echo "${B_RED}🧹 Cleaning: ${RED} $(NAME)"

re: fclean all

.PHONY: all, libft, clean, fclean
