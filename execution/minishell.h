/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/07 16:34:06 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <locale.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_word
{
	char			*word;
	unsigned int	flag;
	struct s_word	*next;
}	t_word;
/* lst functions */
t_word	*ms_lstnew(void *word);
void	ms_lstadd_back(t_word **lst, t_word *new);
void	ms_lst_remove_if(t_word **head);

/* lexx functions */
t_word	*ms_create_word_lst(char *line);
void	ms_word_lst_flag_init(t_word *word);
int		ms_word_assign_flag(char *word);
int		ms_ismeta(char *c);
int		get_word_len(char *line);
int		ms_count_words(char *line);
int		ms_find_next_quotes(char *line);
char	*ms_unquote_words(char *line);

/* free functions */
void	ms_lstclear(t_word **lst);

# endif
