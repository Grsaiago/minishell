/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_eval_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 17:29:19 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/28 17:39:13 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	eval_input(t_shell *s_shell, char *line)
{
	if (!line || !line[0])
		return ;
	else if (!ft_strncmp("pwd", line, 3))
		pwd_cmd();
	else if (!ft_strncmp("env", line, 3))
		env_cmd(s_shell->envp);
	else if (!ft_strncmp("cd", line, 2))
		cd_cmd(s_shell, line);
	else
		printf("Esse comando não existe\n");
	return ;
}
