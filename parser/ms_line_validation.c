/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:34:30 by gsaiago           #+#    #+#             */
/*   Updated: 2023/03/18 22:30:01 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_validate_quote_ammount(char *line)
{
	int	quote_distance;

	if (!line)
		return (1);
	quote_distance = 0;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			quote_distance = ms_find_next_quotes(line);
			if (quote_distance == -1)
				return (1);
			line += quote_distance + 1;
		}
		else
			line++;
	}
	return (0);
}
