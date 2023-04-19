/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/18 22:44:32 by gsaiago          ###   ########.fr       */
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
	struct s_word	*head;
	struct s_list	*env_lst;
	struct s_word	*next;
}	t_word;

/* value for tokens */
enum e_token
{
	MS_WORD = 1,
	MS_PIPE = 2,
	MS_REDIRECT_IN = 4,
	MS_REDIRECT_OUT = 8,
	MS_REDIRECT_FILE = 16,
	MS_APPEND = 32,
	MS_HEREDOC = 64,
};

enum e_builtins
{
	MS_ECHO = 256,
	MS_CD = 512,
	MS_PWD = 1024,
	MS_EXPORT = 2048,
	MS_UNSET = 4096,
	MS_ENV = 8192,
	MS_EXIT = 16384,
};

/* lst */
t_word		*ms_lstnew(void *word);
void		ms_lstadd_back(t_word **lst, t_word *new);
void		ms_lst_remove_if(t_word **head);
int			ms_analyse_lexx(t_word **node);
void		ms_lst_remove_empty_word(t_word **head);
int			ms_flag_word(char *word, int last_flag);
t_list		*ms_create_env_lst(void);
/* parse */
int			ms_parser(char *line, t_word **word_lst, t_list *env);
/* lexx */
t_word		*ms_create_word_lst(char *line, t_list *env_lst);
void		ms_word_lst_flag_init(t_word *word);
int			ms_word_assign_flag(char *word);
int			ms_ismeta(char *c);
int			get_word_len(char *line);
int			ms_count_words(char *line);
int			ms_find_next_quotes(char *line);
int			ms_validate_quote_ammount(char *line);
/* env expansion */
char		*ms_getenv_lst(t_list *env_node, char *env);
char		*ms_expand_env(char *line, t_list *env);
int			ms_get_expanded_env_len(char *line, t_list *env);
void		ms_expand_env_util(char *line, int i, int j, char *ret_line, t_list *env);
void		ms_expand_env_util2(char *line, char *ret_line, int *i, int *j, t_list *env);
int			ms_get_len_after_expansion(char *line, t_list *env);
int			ms_get_env_name_len(char *line);
int			ms_validate_env_name(char *line);
/* remove quotes */
char		*ms_remove_quotes(char *line, int flag);
/* exec*/
char		*ms_check_bin(char *cmd, t_list *env);
char		**ms_get_cmd_mat_from_node(t_word *node);
int			ms_bin_exec(t_word *node, t_list *env);
/* free */
void		ms_lstclear(t_word **lst);
#endif
