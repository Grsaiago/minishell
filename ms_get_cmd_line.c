/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_get_cmd_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 22:08:29 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/17 23:59:15 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name_host(void)
{
	char	*line;
	
	line = ft_strjoin(getenv("USER"), NULL, 0);
	line = ft_strjoin(line, "@", 1);
	line = ft_strjoin(line, getenv("NAME"), 1);
	line = ft_strjoin(line, ":", 1);
	return (line);
}

char	*get_dir_path(t_shell *s_shell)
{
	char	*home_dir;
	char	*cwd;
	int		len;

	home_dir = getenv("HOME");
	cwd = getenv("PWD");
	if (!cwd || !home_dir)
		return (NULL);
	if (!ft_strncmp(home_dir, cwd, ft_strlen(home_dir)))
	{
		s_shell->pre_line = ft_strjoin(s_shell->name_host, "~", 0);
		s_shell->pre_line = ft_strjoin(s_shell->pre_line,
				ft_strlen(home_dir) + cwd, 1);
	}
	else
		s_shell->pre_line = ft_strjoin(s_shell->name_host, cwd, 0);
	s_shell->pre_line = ft_strjoin(s_shell->pre_line, "$ ", 1);
}

