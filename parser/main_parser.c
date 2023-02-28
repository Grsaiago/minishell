/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 17:27:57 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/27 18:51:21 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_func(t_word *word_lst)
{
	while (word_lst)
	{
		printf("Node word > %s\nNode flag > %d\n", word_lst->word, word_lst->flag); //debug
		printf("---------------\n");
		word_lst = word_lst->next;
	}
	return ;
}

int	main(void)
{
	char	*line;
	t_word	*word_lst;

	line = readline("$> ");
	word_lst = ms_create_word_lst(line);
	ms_word_lst_flag_init(word_lst);
	debug_func(word_lst);
	ms_lst_remove_if(&word_lst);
	printf("\nApós passar a lst_remove_if\n");
	debug_func(word_lst);
	ms_lstclear(&word_lst);
	free(line);
	return (0);
}
