/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 18:56:53 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/19 18:59:23 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	g_exit_status;

int	main(void)
{
	char	*line;
	t_list	*env;
	t_word	*word_lst;

	word_lst = NULL;
	env = ms_create_env_lst();
	while (42)
	{
		line = readline("$> ");
		if (!line)
			return (ft_putstr_fd("Exit em", STDOUT_FILENO));
		if (!ft_strncmp(line, "q", 2))
		{
			ft_lstclear(&env, free);
			free(line);
			return (0);
		}
		if (ms_parser(line, &word_lst, env))
			ft_putstr_fd("Error on parser\n", 3);
		if (ms_executor(&word_lst))
			return (0);
		ms_wait_cmds(word_lst);
		ms_lstclear(&word_lst);
	}
	return (0);
}
