/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:19:07 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/18 00:03:31 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	*s_shell;
	int		i;

	i = 0;
	s_shell = &(t_shell){0};
	s_shell->envp = envp;
	s_shell->name_host = get_name_host();
	s_shell->pre_line = get_dir_path(s_shell);
	while (42)
	{
		s_shell->input_line = give_prompt(s_shell->pre_line);
		while (s_shell->input_line[i] == ' ')
			i++;
		eval_input(s_shell, s_shell->input_line + i);
		free(s_shell->input_line);
	}
}
/*
int	main(int argc, char **argv, char **envp)
{
	char	*line;

	printf("envp[0] > |%s|\n", envp[0]);
	while (42)
	{
		line = give_prompt(envp);
		eval_input(line);
		free(line);
	}
}
*/
