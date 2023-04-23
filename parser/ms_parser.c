/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:42:31 by gsaiago           #+#    #+#             */
/*   Updated: 2023/04/22 21:07:11 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ms_parser(char *line, t_word **word_lst, t_list *env)
{
	int	err;

	err = 0;
	*word_lst = NULL;
	if (ms_validate_quote_ammount(line))
	{
		printf("Syntax error: There is an unclosed quote\n");
		free(line);
		return (-1);
	}
	*word_lst = ms_create_word_lst(line, env);
	err = ms_lexxer(word_lst);
	if (line[0])
		add_history(line);
	free(line);
	return (err);
}
