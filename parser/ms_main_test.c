/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:26:37 by gsaiago           #+#    #+#             */
/*   Updated: 2022/12/21 22:38:28 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
t_word	*ms_create_word_lst(char *line);
void	ms_word_lst_clear(t_word *head);

int	main(void)
{
	char	*str;
	t_word	*word_lst;
	t_word	*aux;
	int		i;

	i = 0;
	str = readline("Insert input$ ");
	word_lst = ms_create_word_lst(str);
	aux = word_lst;
	while (word_lst)
	{
		printf("word {%d} > |%s|\n", i, word_lst->word);
		i++;
		word_lst = word_lst->next;
	}
	ms_word_lst_clear(aux);
	return (0);
}
