/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_executor_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:30:55 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/29 13:27:32 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_has_pipe(t_word *node)
{
	while (node)
	{
		if (node->flag == MS_PIPE)
			return (0);
		node = node->next;
	}
	return (1);
}

void	ms_exec_pipe(t_word *node, t_list **env_lst)
{
	uint16_t	builtin;

	builtin = is_builtin(node);
	node->pid = fork();
	if (node->pid != 0)
		return ;
	if (!builtin)
		ms_bin_exec_pipe(node, *env_lst);
	else
		ms_builtin_exec_pipe(node, env_lst, builtin);
}

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
