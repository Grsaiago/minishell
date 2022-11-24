/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:50:17 by gsaiago           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/23 23:49:31 by gsaiago          ###   ########.fr       */
=======
/*   Updated: 2022/11/23 15:56:25 by gsaiago          ###   ########.fr       */
>>>>>>> 36e01eddc3ad31a98e68e611fc2c60ad75c62888
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_user_input(char *prompt_msg)
{
	char	*line;

	line = readline(prompt_msg);
	add_history(line);
	return (line);
}

char	*get_name_host(void)
{
	char	*line;
	
	line = ft_strjoin(getenv("USER"), "@", 0);
	line = ft_strjoin(line, getenv("NAME"), 1);
	line = ft_strjoin(line, ":", 1);
	return (line);
}

void	get_prompt_msg(t_shell *s_shell)
{
	char	*home_dir;
	char	*cwd;
	int		len;

	home_dir = getenv("HOME");
	cwd = getcwd(NULL, 0);
	if (s_shell->prompt)
		free(s_shell->prompt);
	if (!cwd || !home_dir)
	{
		s_shell->prompt = NULL;
		return ;
	}
	else if (!ft_strncmp(home_dir, cwd, ft_strlen(home_dir)))
	{
		s_shell->prompt = ft_strjoin(s_shell->name_host, "~", 0);
		s_shell->prompt = ft_strjoin(s_shell->prompt, cwd + ft_strlen(home_dir), 1);
	}
	else
		s_shell->prompt = ft_strjoin(s_shell->name_host, cwd, 0);
	free(cwd);
	s_shell->prompt = ft_strjoin(s_shell->prompt, "$ ", 1);
}

