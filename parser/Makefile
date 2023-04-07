# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 17:37:55 by gsaiago           #+#    #+#              #
#    Updated: 2023/04/07 17:53:30 by gsaiago          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser

STEP_NAME = step_parser

SRCS = $(wildcard *.c) \
	   ../execution/ms_redirects.c \

CC = cc 

LIBFT_PATH = ../libft

LIBFT = $(LIBFT_PATH)/libft.a
CFLAGS = -g -Wall -Wextra

LIBFT_LINK = -L$(LIBFT_PATH) -lft

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) -DMAIN  $(SRCS) -o $(NAME) -lreadline $(LIBFT_LINK)

step: $(STEP_NAME)

$(STEP_NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) -DSTEP  $(SRCS) -o $(STEP_NAME) -lreadline $(LIBFT_LINK)

$(LIBFT): 
	make -C $(LIBFT_PATH)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	rm -f $(STEP_NAME)
	rm -rf $(STEP_NAME).dSYM
	make clean -C $(LIBFT_PATH)

re: clean all

fclean: clean
	make fclean -C $(LIBFT_PATH)

.PHONY:
	all re clean fclean

