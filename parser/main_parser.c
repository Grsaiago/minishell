/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/12 23:44:00 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ms_parser(char *line, t_word **word_lst);
char	*ms_remove_quotes(char *line, int flag);

void	debug_func(t_word *word_lst)
{
	static int	exec_times = 0;

	printf ("Execução No: %d\n", exec_times);
	while (word_lst)
	{
		printf("Node word > %s\nNode flag > %d\n", word_lst->word, word_lst->flag); //debug
		printf("---------------\n");
		word_lst = word_lst->next;
	}
	exec_times++;
	return ;
}

/* main test */
int	main(void)
{
	char	*line;
	t_word	*word_lst;

	word_lst = NULL;
	while (42)
	{
		line = readline("$> ");
		if (!ft_strncmp(line, "q", 2))
		{
			free(line);
			return (0);
		}
		if (ms_parser(line, &word_lst))
			ft_putstr_fd("Error on parser\n", 3);
		debug_func(word_lst);
		ms_lstclear(&word_lst);
	}
	return (0);
}

/* test for quote remove
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
		line = ms_remove_quotes(line, 1);
		free(line);
	}
	return (0);

}
*/
