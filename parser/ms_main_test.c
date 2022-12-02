/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:26:37 by gsaiago           #+#    #+#             */
/*   Updated: 2022/12/01 17:56:20 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words(char *line);
int	count_word_len(char *word);
char	**ms_split_input(char *line);

int	main(void)
{
	char	*str;
	char	**mat;
	int		i;

	i = 0;
	str = readline("Insert input$ ");
	mat = ms_split_input(str);
	printf("count words > |%d|\n", count_words(str));
	printf("word len > |%d|\n", count_word_len(str));
	while (mat[i])
	{
		printf("mat[%d] > %s\n", i, mat[i]);
		i++;
	}


	free(str);
//	ft_free_mat(mat);
	return (0);
}
