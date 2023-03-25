# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/19 23:00:31 by gsaiago           #+#    #+#              #
#    Updated: 2023/03/25 00:49:20 by gsaiago          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = env 

SRCS = $(wildcard *.c)\
	   ../parser/ms_parser.c \
	   ../parser/ms_line_validation.c \
	   ../parser/ms_utils_wordcount.c \
	   ../parser/ms_create_word_lst.c \
	   ../parser/ms_utils_expand_env.c \
	   ../parser/ms_utils_expand_env2.c \
	   ../parser/ms_utils_remove_quotes.c \
	   ../parser/ms_utils_lst.c \

CC = cc 

LIBFT_PATH = ../libft

LIBFT = $(LIBFT_PATH)/libft.a
CFLAGS = -g -Wall -Wextra

LIBFT_LINK = -L$(LIBFT_PATH) -lft

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lreadline $(LIBFT_LINK)

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
