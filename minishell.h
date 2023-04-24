/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/24 20:02:41 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <locale.h>
# include <signal.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

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
t_word	*ms_lstnew(void *word);
void	ms_lstadd_back(t_word **lst, t_word *new);
void	ms_lst_remove_if(t_word **head);
int		ms_analyze_lexx(t_word **node);
void	ms_lst_remove_empty_word(t_word **head);
int		ms_flag_word(char *word, int last_flag);
t_list	*ms_create_env_lst(void);
/* parser */
int		ms_parser(char *line, t_word **word_lst, t_list *env);
t_word	*ms_create_word_lst(char *line, t_list *env_lst);
void	ms_word_lst_flag_init(t_word *word);
int		ms_word_assign_flag(char *word);
int		ms_ismeta(char *c);
int		get_word_len(char *line);
int		ms_count_words(char *line);
int		ms_find_next_quotes(char *line);
int		ms_validate_quote_ammount(char *line);
/* lexx */
int		ms_lexxer(t_word **word_lst);
int		ms_analyze_lexx(t_word **lst);
int		ms_analyze_syntax(t_word *word_lst);
int		ms_analyze_pipe_syntax(t_word *word_lst);
int		ms_analyze_redirect_syntax(t_word *word_lst);
/* env expansion */
char	*ms_getenv_lst(t_list *env_node, char *env);
char	*ms_expand_env(char *line, t_list *env);
int		ms_get_expanded_env_len(char *line, t_list *env);
void	ms_expand_env_util(char *line, int i, int j, char *ret_line, t_list *env);
void	ms_expand_env_util2(char *line, char *ret_line, int *i, int *j, t_list *env);
int		ms_get_len_after_expansion(char *line, t_list *env);
int		ms_get_env_name_len(char *line);
int		ms_validate_env_name(char *line);
t_word	*ms_get_next_command(t_word *node);
/* remove quotes */
char	*ms_remove_quotes(char *line, int flag);
/* builtins */
int		ms_cd(t_word *node);
int		ms_update_env(t_list *env_lst, char *ref, char *newvalue);
int		ms_echo(t_word *node);
int		ms_env(t_word *node);
int		ms_export(t_word *node);
int		ms_pwd(t_word *node);
int		ms_unset(t_word *node, t_list **env);
void	ms_delete_env(t_list **node, char *ref);
__attribute__((noreturn))
void	ms_exit(t_word **word, t_list **env_lst);
/* exec*/
int		ms_executor(t_word **lst, t_list **env_lst);
void	ms_builtin_exec(t_word *node, t_list **env_lst, uint16_t builtin);
int		is_builtin(t_word *node);
int		ms_bin_exec(t_word *node, t_list *env_lst);
char	*ms_check_bin(char *cmd, t_list *env);
char	**ms_get_cmd_mat_from_node(t_word *node);
void	ms_close_sentence_fd(t_word *node);
void	ms_close_all_fd(t_word *node);
t_word	*clean_sentence_redirections(t_word **lst, int flag);
void	ms_wait_cmds(t_word *node);
/* redirections */
int		ms_do_redirections(t_word *word_lst);
int		ms_redirect_in(t_word *node);
int		ms_redirect_out(t_word *node);
int		ms_heredoc(t_word* node);
int		ms_pipe(t_word *node);
/* free */
void	ms_lstclear(t_word **lst, int flag);
#endif
