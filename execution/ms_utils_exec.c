/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 15:33:15 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 09:21:08 by kefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ms_close_all_fd(t_word *node);

char	**ms_get_cmd_mat_from_node(t_word *node)
{
	t_word				*aux;
	char				**mat;
	unsigned int		mat_positions;
	unsigned int		i;

	if (!node)
		return (NULL);
	aux = node;
	i = -1;
	mat_positions = 0;
	while (aux && aux->flag == MS_WORD)
	{
		aux = aux->next;
		mat_positions++;
	}
	mat = ft_calloc(mat_positions + 1, sizeof(char *));
	if (!mat)
		return (NULL);
	while (++i < mat_positions)
	{
		mat[i] = ft_strdup(node->word, 0);
		node = node->next;
	}
	return (mat);
}

void	ms_wait_cmds(t_word *node)
{
	t_word				*aux;
	extern unsigned int	g_exit_status;

	if (!node)
		return ;
	aux = node;
	while (node)
	{
		if (node->pid != 0)
			waitpid(node->pid, &node->ret, 0);
		node = node->next;
	}
	node = aux;
	while (node)
	{
		if (node->ret >= 0)
			g_exit_status = WEXITSTATUS(node->ret);
		node = node->next;
	}
	return ;
}
