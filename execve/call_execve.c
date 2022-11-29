/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   call_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguedes <gguedes@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:58:52 by gguedes           #+#    #+#             */
/*   Updated: 2022/11/29 14:18:16 by gguedes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ms_exec.h"

char	*get_path(char *cmd)
{
	
}

int	call_execve(char **cmd, char **envp)
{
	char	*path;

	path = get_path(cmd[0]);
	execve(path, cmd, envp);
}
