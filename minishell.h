/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/25 00:36:42 by gsaiago          ###   ########.fr       */
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
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_word
{
	char			*word;
	unsigned int	flag;
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	struct s_list	*env_lst;
	struct s_word	*next;
}	t_word;

/* flags for words */
# define MS_WORD 1
# define MS_PIPE 2
# define MS_REDIRECT_IN 3
# define MS_REDIRECT_OUT 4
# define MS_HEREDOC 5
# define MS_APPEND 6
/* lst */
t_word	*ms_lstnew(void *word);
void	ms_lstadd_back(t_word **lst, t_word *new);
void	ms_lst_remove_if(t_word **head);
int		ms_clean_words_and_init_flags_on_lst(t_word **node);
void	ms_lst_remove_empty_word(t_word **head);
int		ms_flag_word(t_word *node);
t_list	*ms_create_env_lst(void);
/* parse */
int		ms_parser(char *line, t_word **word_lst);
/* lexx */
t_word	*ms_create_word_lst(char *line);
void	ms_word_lst_flag_init(t_word *word);
int		ms_word_assign_flag(char *word);
int		ms_ismeta(char *c);
int		get_word_len(char *line);
int		ms_count_words(char *line);
int		ms_find_next_quotes(char *line);
int		ms_validate_quote_ammount(char *line);
/* env expansion */
char	*ms_expand_env(char *line);
int		ms_get_expanded_env_len(char *line);
void	ms_expand_env_util(char *line, int i, int j, char *ret_line);
void	ms_expand_env_util2(char *line, char *ret_line, int *i, int *j);
int		ms_get_len_after_expansion(char *line);
int		ms_get_env_name_len(char *line);
int		ms_validate_env_name(char *line);
/* remove quotes */
char	*ms_remove_quotes(char *line, int flag);
void	ms_null_start_end_quotes(char *line);
/* exec*/
char	*ms_check_bin(char *cmd);
char	**ms_create_mat_from_lst(t_word *node);
int		ms_bin_exec(t_word *node);
/* free */
void	ms_lstclear(t_word **lst);
#endif
