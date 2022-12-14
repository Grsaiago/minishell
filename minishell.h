/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:04:32 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/28 20:29:20 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <locale.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_shell
{
	char 	*name_host;
	char	*dir_line;
	char	*prompt;
	char	*input_line;
	char	**path_mat;
	char	**envp;
	char	***argv_array;
}	t_shell;

/* INPUT SANITIZATION */
int		count_phrases(char *line);
int		word_len(char *line);
int		next_quotes(char *line);
char	**ms_split_phrases(char *line, int flag);
char	***create_argv_array(t_shell s_shell);
int		initialize_shell_struct(t_shell *s_shell, char **envp);
char	*ft_remove_quotes(char *str);
int		is_meta_character(char c);
/* PROMPT CONTROL */
char	*get_name_host(void);
void	get_prompt_msg(t_shell *s_shell);
char	*get_env(char **envp, char *line);
int		find_envp_line(char **envp, char *find);
char	*get_user_input(char *prompt_msg);
/* COMMANDS */
char 	*get_cmd_path(t_shell *s_shell, char *cmd);
void	eval_input(t_shell *s_shell, char *line);
void	env_cmd(char **envp);
void	pwd_cmd(void);
void 	cd_cmd(t_shell *s_shell, char *line);
#endif
