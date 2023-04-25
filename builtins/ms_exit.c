/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/22 19:55:48 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/24 21:42:55 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

__attribute__((noreturn))
void	ms_exit(t_word *node, t_word **word, t_list **env_lst)
{
	extern int	g_exit_status;
	int			param;
	int			i;
	char		*arg1;
	char		**arg_mat;


	param = g_exit_status;
	i = -1;
	arg_mat = ms_get_cmd_mat_from_node(node);
	if (arg_mat && arg_mat[1])
	{
		arg1 = arg_mat[1];
		while (arg1[++i])
			if (!ft_isdigit(arg1[i]))
		param = ft_atoi(arg_mat[1]);
		ft_free_mat(arg_mat);
	}
	ft_lstclear(env_lst, free);
	ms_lstclear(word, 0);
	rl_clear_history();
	g_exit_status = 0;
	exit(param);
}
