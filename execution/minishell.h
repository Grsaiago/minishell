/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/08 15:54:31 by gsaiago          ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

/*
union u_token
{
	struct s_word		*token_word;
	struct s_pipe 		*token_pipe;
	struct s_redirect	*token_redirect;
	struct s_appen		*token_append;
	struct s_heredoc	*token_heredoc;
}	u_token;

typedef struct s_pipe
{
	int				pipe[2];
	struct s_node	*node;
}	t_pipe;

typedef struct s_node
{
	char			*word;
	char			flag;
	struct s_node	*next;
	union u_token	*token;
} t_node;

typedef struct s_cmd
{
	int				fd_in;
	int				fd_out;
	pid_t			pid;
	struct s_node	*head;
	struct s_list	*env_lst;
	struct s_node	*node;
} t_cmd;
*/

typedef struct s_word
{
	char			*word;
	unsigned int	flag;
	int				fd_in;
	int				fd_out;
	int				pipe[2];
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

/* lst */
t_word	*ms_lstnew(void *word);
void	ms_lstadd_back(t_word **lst, t_word *new);
void	ms_lst_remove_if(t_word **head);
int		ms_clean_words_and_init_flags_on_lst(t_word **node);
void	ms_lst_remove_empty_word(t_word **head);
int		ms_flag_word(t_word *node);
t_list	*ms_create_env_lst(void);
/* parse */
int		ms_parser(char *line, t_word **word_lst, t_list *env);
/* lexx */
t_word	*ms_create_word_lst(char *line, t_list *env_lst);
void	ms_word_lst_flag_init(t_word *word);
int		ms_word_assign_flag(char *word);
int		ms_ismeta(char *c);
int		get_word_len(char *line);
int		ms_count_words(char *line);
int		ms_find_next_quotes(char *line);
int		ms_validate_quote_ammount(char *line);
/* env expansion */
char	*ms_getenv_lst(t_list *env_node, char *env);
char	*ms_expand_env(char *line, t_list *env);
int		ms_get_expanded_env_len(char *line, t_list *env);
void	ms_expand_env_util(char *line, int i, int j, char *ret_line, t_list *env);
void	ms_expand_env_util2(char *line, char *ret_line, int *i, int *j, t_list *env);
int		ms_get_len_after_expansion(char *line, t_list *env);
int		ms_get_env_name_len(char *line);
int		ms_validate_env_name(char *line);
/* remove quotes */
char	*ms_remove_quotes(char *line, int flag);
/* exec*/
char	*ms_check_bin(char *cmd, t_list *env);
char	**ms_get_cmd_mat_from_node(t_word *node);
int		ms_bin_exec(t_word *node, t_list *env);
/* free */
void	ms_lstclear(t_word **lst);
#endif
