/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_redirects.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:26:04 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/29 15:53:48 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_redirect_out(t_word *node)
{
	int	new_fd;

	if (!node->next || node->next->flag != MS_WORD)
	{
		//print erro;
		return (-1);
	}
	new_fd = open(node->next->word, O_CREAT | O_TRUNC, S_IRWXU | S_IRWXG | S_IRWXO);
	if (new_fd == -1)
	{
		//print erro;
		return (-1);
	}
	node = node->next;
	while (node && node->flag != MS_REDIRECT_IN
			&& node->flag != MS_REDIRECT_OUT)
	{
		node->fd_out = new_fd;
		node = node->next;
	}
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
	while (node)
	{
		if (node->flag == MS_REDIRECT_OUT)
			error = ms_redirect_out(node);
		else if (node->flag == MS_REDIRECT_IN)
			//ms_redirect_in(node);
		if (error == -1)
			break;
		node = node->next;
	}
	if (error != 0)
		;
		//clear_redirects
	return (error);
}
