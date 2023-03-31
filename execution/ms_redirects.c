/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:26:04 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/30 22:51:03 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ms_reattribute_in_out(t_word *node, int fd, int in_out);

int	ms_redirect_cmd_out(t_word *node)
{
	int		fd;
	t_word	*head;

	head = node;
	fd = STDOUT_FILENO;
	while (node && node->flag != MS_PIPE) 
	{
		if (node->flag == MS_REDIRECT_OUT)
		{
			//if (head->fd_out != STDOUT_FILENO)
			//	close(head->fd_out);
			fd = open(node->next->word, O_WRONLY | O_CREAT | O_TRUNC, 0777);
			if (fd == -1)
			{
				//print erro;
				return (-1);
			}
		}
		node = node->next;
	}
	if (fd)
		head->fd_out = fd;
	return (0);
}

void	ms_reattribute_in_out(t_word *node, int fd, int in_out)
{
	if (in_out == STDOUT_FILENO)
	{
		while (node && node->flag != MS_PIPE)
		{
			if (node->flag == MS_WORD)
				node->fd_out = fd;
			node = node->next;
		}
	}
	else
	{
		while (node && node->flag != MS_PIPE)
		{
			if (node->flag == MS_WORD)
				node->fd_in = fd;
			node = node->next;
		}
	}
	return ;
}

int	ms_do_redirections(t_word **word_lst)
{
	t_word	*node;
	int		error;

	if (!word_lst || !*word_lst)
		return (-1);
	error = 0;
	node = *word_lst;
	while (node)
	{
		//ms_redirect_cmd_in(node);
		ms_redirect_cmd_out(node);
		while (node && node->flag != MS_PIPE)
			node = node->next;
		if (node)
			node = node->next;
	}
	//clear_redirects
	return (error);
}
