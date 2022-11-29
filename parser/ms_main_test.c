/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_main_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 20:26:37 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/28 21:28:07 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(void)
{
	char	*str;
	char	**phrase_mat;
	int		i;

	i = 0;
	str = readline("Insert input$ ");
	phrase_mat = ms_split_phrases(str, 1);
	while (phrase_mat[i])
	{
		printf("Phrase %d > |%s|\n", i, phrase_mat[i]);
		i++;
	}
	ft_free_mat(phrase_mat);
	return (0);
}
