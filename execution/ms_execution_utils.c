/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execution_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 13:28:16 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 13:30:14 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_close_sentence_fd(t_word *node)
{
	while (node && node->flag != MS_PIPE)
	{
		if (node->fd_in != STDIN_FILENO)
			close(node->fd_in);
		if (node->fd_out != STDOUT_FILENO)
			close(node->fd_out);
		node = node->next;
	}
	return ;
}

t_word	*ms_get_next_command(t_word *node)
{
	while (node)
	{
		if (node->flag == MS_PIPE)
			return (node->next);
		node = node->next;
	}
	return (node);
}

t_word	**ms_get_next_cmd_addr(t_word *node)
{
	while (node && node->flag != MS_PIPE)
		node = node->next;
	if (node)
		return (&node->next);
	else
		return (NULL);
}
