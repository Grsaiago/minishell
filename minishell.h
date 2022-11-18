/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:04:32 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/18 00:03:07 by gsaiago          ###   ########.fr       */
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
	char	*pre_line;
	char	*input_line;
	char	**envp;
}	t_shell;

/* PROMPT CONTROL */
char	*get_name_host(void);
char	*get_dir_path(t_shell *s_shell);
char	*get_env(char **envp, char *line);
int		find_envp_line(char **envp, char *find);
char	*give_prompt(char *line);
/* COMMANDS */
void	eval_input(t_shell *s_shell, char *line);
void	env_cmd(char **envp);
void	pwd_cmd(void);
void 	cd_cmd(t_shell *s_shell, char *line);
#endif
