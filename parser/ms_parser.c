/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:42:31 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/07 16:35:52 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int	ms_validate_quote_ammount(char *line);

int	ms_parser(char *line, t_word **word_lst)
{
	*word_lst = NULL;
	if (line)
	{
		if (ms_validate_quote_ammount(line))
		{
			free(line);
			printf("Error!\nThere is an unclosed quote\n");
		}
		else
		{
			*word_lst = ms_create_word_lst(line);
			free(line);
			if (!word_lst)
				return (1);
			//ms_word_lst_flag_init(*word_lst);
			//ms_lst_remove_if(word_lst);
		}
	}
	return (0);
}
