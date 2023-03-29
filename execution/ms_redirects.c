/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:26:04 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/29 16:24:08 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void	ms_reattribute_in_out(t_word *node, int in_out, int fd);

int	ms_redirect_out(t_word **word_lst)
{
	int		final_fd;
	t_word	*node;

	node = *word_lst;
	while (node)
	{
		if (node->flag == MS_REDIRECT_OUT)
			final_fd = open(node->next->word, O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
		if (final_fd == -1)
		{
			//print erro;
			return (-1);
		}
		node = node->next;
	}
	ms_reattribute_in_out(*word_lst, 1, final_fd);
	return (0);
}

int	ms_do_redirections(t_word **word_lst)
{
	t_word	*node;
	int		error;

	if (!word_lst || !*word_lst)
		return (-1);
	error = 0;
	node = *word_lst;
	if (ms_redirect_out(word_lst) == -1)
		return (-1);
	// || ms_redirect_in(word_lst)
	// {
	// 		print de erro;
	// 		return (-1);
	// }
	//clear_redirects
	return (error);
}

void	ms_reattribute_in_out(t_word *node, int in_out, int fd)
{
	if (in_out == 0)
	{
		while (node)
		{
			node->fd_in= fd;
			node = node->next;
		}
	}
	else 
	{
		while (node)
		{
			node->fd_out = fd;
			node = node->next;
		}
	}
	return ;
}
