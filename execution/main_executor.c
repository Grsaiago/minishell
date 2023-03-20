/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_executor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/19 23:02:38 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/20 15:34:57 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char 	**create_mat_from_lst(t_word *node);
char	*ms_check_bin(char *cmd);
char 	**ms_create_mat_from_lst(t_word *node);
int		ms_bin_exec(t_word *node);

void	debug_func(t_word *word_lst, char **mat)
{
	static int	exec_times = 0;
	int			i = 0;

	printf ("Execução No: %d\n", exec_times);
	while (word_lst)
	{
		printf("NODE %d\n", i);
		printf("Node word > %s\nNode flag > %d\n", word_lst->word, word_lst->flag); //debug
		word_lst = word_lst->next;
		printf("---------------\n");
		i++;
	}
	for (int i = 0; mat[i]; i++)
		printf("Posição mat[%d] > %s\n", i, mat[i]);
	exec_times++;
	return ;
}

int	main(void)
{
	char	*line;
//	char	**mat;
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
		//debug_func(word_lst, mat);
		ms_bin_exec(word_lst);
		ms_lstclear(&word_lst);
		//ft_free_mat(mat);
	}
	return (0);
}
