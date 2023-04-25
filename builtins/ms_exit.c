/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:55:48 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/24 20:03:37 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

__attribute__((noreturn))
void	ms_exit(t_word **word, t_list **env_lst)
{
	extern int	g_exit_status;

	ft_lstclear(env_lst, free);
	ms_lstclear(word, 0);
	rl_clear_history();
	g_exit_status = 0;
	exit(0);
}