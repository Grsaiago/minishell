/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 00:42:32 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/23 16:22:19 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_env(t_word *node)
{
	t_list	*env;

	if (node)
		env = node->env_lst;
	else
		env = NULL;
	while (env)
	{
		ft_putstr_fd(env->content, node->fd_out);
		ft_putchar_fd('\n', node->fd_out);
		env = env->next;
	}
	return (0);
}
