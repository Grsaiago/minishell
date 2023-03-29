/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/29 15:51:51 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_func(t_word *word_lst)
{
	static int	exec_times = 0;

	printf ("Execução No: %d\n", exec_times);
	while (word_lst)
	{
		printf("Node word > %s\nNode flag > %d\nNode fd_in > %d\nNode fd_out : %d\n", word_lst->word, word_lst->flag, word_lst->fd_in, word_lst->fd_out); //debug
		printf("---------------\n");
		word_lst = word_lst->next;
	}
	exec_times++;
	return ;
}

/* test for variable expansion
int	main(void)
{
	char	*line;

	while (42)
	{
		line = readline("$> ");
		if (!ft_strncmp(line, "q", 2))
		{
			free(line);
			return (0);
		}
		printf("Lenght da linha > %ld\nRetorno da ms_get_len_after_expansion > %d\n", ft_strlen(line), ms_get_len_after_expansion(line));
		free(line);
	}
	return (0);
}
*/

/* main test */
int	main(void)
{
	char	*line;
	t_word	*word_lst;
	t_list	*env_lst;

	env_lst = ms_create_env_lst();
	word_lst = NULL;
	while (42)
	{
		line = readline("$> ");
		if (!ft_strncmp(line, "q", 2))
		{
			free(line);
			return (0);
		}
		if (ms_parser(line, &word_lst, env_lst))
			ft_putstr_fd("Error on parser\n", 3);
		debug_func(word_lst);
		ms_lstclear(&word_lst);
	}
	return (0);
}

/*
int	main(void)
{
	char	*line;

	while (42)
	{
		line = readline("$> ");
		if (!ft_strncmp(line, "q", 2))
		{
			free(line);
			return (0);
		}
		line = ms_expand_env(line);
		printf("line depois de env exp > %s\n", line); // debug
		line = ms_remove_quotes(line, 1);
		printf("line depois de remove quotes> %s\n", line); // debug
		free(line);
	}
	return (0);
}
*/
