/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 16:20:44 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/07 16:20:45 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_echo(t_word *node)
{
	uint8_t	newline;

	newline = 1;
	if (node->next)
	{
		if (!ft_strncmp(node->next->word, "-n", 3))
		{
			newline = 0;
			node = node->next;
		}
		while (node && node->flag != MS_PIPE)
		{
			ft_putstr_fd(node->word, node->fd_out);
			node = node->next;
			if (node && node->flag != MS_PIPE)
				ft_putstr_fd(" ", node->fd_out);
		}
	}
	if (newline)
		printf("\n");
	//status de saída global
	return (0);
}

/*
int	main(void)
{
	char	*mat[6] = {"echo", "-n", "oieoi", "shishd", "lkdbfkjsagk", NULL};
	int		count = 6;

	ms_echo(4, mat);
	return(0);
}
*/
