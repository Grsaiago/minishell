/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 19:11:09 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/19 12:36:25 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ms_close_all_fd(t_word *node);

int	ms_pipe(t_word *node)
{
	int		fd[2];
	t_word	*cmd;

	while (node)
	{
		while (node && node->flag != MS_PIPE && node->flag != MS_WORD) 
			node = node->next;
		cmd = node;
		while (node && node->flag != MS_PIPE)
			node = node->next;
		if (!node)
			return (0);
		if (pipe(fd) == -1)
			return (1);
		cmd->fd_out = fd[1];
		node = node->next;
		cmd = node;
		while (cmd && cmd->flag != MS_PIPE && cmd->flag != MS_WORD) 
			cmd = cmd->next;
		if (cmd)
			cmd->fd_in = fd[0];
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (0);
}

void	ms_close_all_fd(t_word *node)
{
	while (node)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		else if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		node = node->next;
	}
	return ;
}
