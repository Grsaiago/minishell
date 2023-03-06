/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_line_validation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:34:30 by gsaiago           #+#    #+#             */
/*   Updated: 2023/02/28 11:39:58 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_validate_quote_ammount(char *line)
{
	int	single_quotes;
	int	double_quotes;

	if (!line)
		return (0);
	single_quotes = 0;
	double_quotes = 0;
	while (*line)
	{
		if (*line == '\'')
			single_quotes++;
		else if (*line == '\"')
			double_quotes++;
		line++;
	}
	if ((single_quotes % 2 != 0) || (double_quotes % 2 != 0))
		return (1);
	return (0);
}
