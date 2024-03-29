# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/22 17:02:28 by gsaiago           #+#    #+#              #
#    Updated: 2023/04/29 13:30:57 by gsaiago          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	./ms_main.c \
		./parser/ms_parser.c \
		./parser/ms_flag_words.c \
		./parser/ms_analyze_syntax.c \
		./parser/ms_analyze_syntax2.c \
		./parser/ms_create_word_lst.c \
		./parser/ms_expand_env.c \
		./parser/ms_expand_env2.c \
		./parser/ms_getenv_lst.c \
		./parser/ms_line_validation.c \
		./parser/ms_remove_quotes.c \
		./parser/ms_utils_lst.c \
		./parser/ms_utils_free.c \
		./execution/ms_executor.c \
		./execution/ms_execution_utils.c \
		./execution/ms_pipe.c \
		./execution/ms_redirects.c \
		./execution/ms_bin_exec.c \
		./execution/ms_utils_exec.c \
		./execution/ms_executor_pipe.c \
		./builtins/ms_cd.c \
		./builtins/ms_echo.c \
		./builtins/ms_env.c \
		./builtins/ms_pwd.c \
		./builtins/ms_unset.c \
		./builtins/ms_export.c \
		./builtins/ms_exit.c \

CC = cc 

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

CFLAGS = -g -Wall -Wextra -Werror

CPPFLAGS = -I /opt/homebrew/Cellar/readline/8.2.1/include

CPPFLAGS += -I ~/.brew/opt/readline/include

LDFLAGS += -L ~/.brew/opt/readline/lib

LIBFT_LINK = -L$(LIBFT_PATH) -lft

CPPFLAGS = -I /opt/homebrew/Cellar/readline/8.2.1/include

CPPFLAGS += -I ~/.brew/opt/readline/include

LDFLAGS += -L ~/.brew/opt/readline/lib

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) -o $(NAME) -lreadline $(CPPFLAGS) $(LDFLAGS) $(LIBFT_LINK)

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
