/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:30:55 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 09:01:33 by kefernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_exit_pipe(t_word **word, t_list **env_lst);

void	ms_builtin_exec_pipe(t_word *node, t_list **env_lst, uint16_t builtin)
{
	if (builtin == MS_ECHO)
		exit(ms_echo(node));
	else if (builtin == MS_CD)
		exit(ms_cd(node));
	else if (builtin == MS_PWD)
		exit(ms_pwd(node));
	else if (builtin == MS_EXPORT)
		exit(ms_export(node));
	else if (builtin == MS_ENV)
		exit(ms_env(node));
	else if (builtin == MS_UNSET)
		exit(ms_unset(node, env_lst));
	else if (builtin == MS_EXIT)
		exit(ms_exit_pipe(&node, &node->env_lst));
	return ;
}
