# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 17:37:55 by gsaiago           #+#    #+#              #
#    Updated: 2022/11/28 17:39:01 by gsaiago          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = parser

SRCS = $(wildcard *.c)

CC = cc 

LIBFT_PATH = ../libft

LIBFT = $(LIBFT_PATH)/libft.a
CFLAGS = -g

LIBFT_LINK = -L$(LIBFT_PATH) -lft

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT_LINK) -lreadline -o $(NAME)

$(LIBFT): 
	make -C $(LIBFT_PATH)

clean:
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	make clean -C $(LIBFT_PATH)

re: clean all

fclean: clean
	make fclean -C $(LIBFT_PATH)

.PHONY:
	all re clean fclean

