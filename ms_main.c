/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:19:07 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/21 17:33:22 by gsaiago          ###   ########.fr       */
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
	get_prompt_msg(s_shell);
	while (42)
	{
		s_shell->input_line = get_user_input(s_shell->prompt);
		while (s_shell->input_line[i] == ' ')
			i++;
		eval_input(s_shell, s_shell->input_line + i);
		free(s_shell->input_line);
	}
}

char	*get_execv_output(char *pathname)
{


}

/* TEST MAIN */

/*
int	main(int argc, char **argv, char **envp)
{
	t_shell	*s_shell;
	int	i;

	i = -1;
	s_shell = &(t_shell){0};
	initialize_shell_struct(s_shell, envp);
	printf("%s\n", get_cmd_path(s_shell, "cd"));
	while (s_shell->path_mat[++i])
		free(s_shell->path_mat[i]);
	free(s_shell->path_mat);
}
*/
