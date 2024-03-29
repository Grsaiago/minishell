/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:20:44 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 08:26:02 by kefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_echo(t_word *node)
{
	uint8_t	newline;
	t_word	*head;

	head = node;
	newline = 1;
	if (node->next)
	{
		if (!ft_strncmp(node->next->word, "-n", 2))
		{
			newline = 0;
			node = node->next;
		}
		node = node->next;
		while (node && node->flag != MS_PIPE)
		{
			ft_putstr_fd(node->word, head->fd_out);
			node = node->next;
			if (node && node->flag != MS_PIPE)
				ft_putchar_fd(' ', head->fd_out);
		}
	}
	if (newline)
		ft_putchar_fd('\n', head->fd_out);
	return (0);
}
