/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:42:31 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/18 22:32:36 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ms_validate_quote_ammount(char *line);

int	ms_parser(char *line, t_word **word_lst)
{
	*word_lst = NULL;
	if (ms_validate_quote_ammount(line))
	{
		printf("Syntax error: There is an unclosed quote\n");
		free(line);
		return (1);
	}
	*word_lst = ms_create_word_lst(line);
	if (!word_lst)
		return (1);
	//ms_word_lst_flag_init(*word_lst);
	//ms_lst_remove_if(word_lst);
	free(line);
	return (0);
}
