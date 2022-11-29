/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguedes <gguedes@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:22:49 by gguedes           #+#    #+#             */
/*   Updated: 2022/11/29 14:47:36 by gguedes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

static int	check(char ***argv_v)
{
	if (!ft_strcmp(argv_v, "<<"))
		call_heredoc();
	else if (!ft_strcmp(argv_v, "<"))
		setup(argv_v, O_RDONLY);
	else if (!ft_strcmp(argv_v, ">"))
		setup(argv_v, O_WRONLY);
	else if (!ft_strcmp(argv_v, ">>"))
		setup(argv_v, O_APPEND);
}

static int	setup(char *file, int perm)
{
	int	fd;

	fd = open(file, perm);
	dup2(STDIN_FILENO, fd);
}

int	redirect(char ***argv_v)
{
	int	fd;

	fd = STDIN_FILENO;
	while (!ft_strcmp(**argv_v, "|") && argv_v)
	{
		check(argv_v);
		argv_v++;
	}
	return (fd);
}