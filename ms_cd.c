/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:03:36 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/17 23:54:45 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void cd_cmd(t_shell *s_shell, char *line)
{
	int	i;

	i = 1;
	while (line[i] == ' ')
		i++;
	if (!line[i])
		chdir(getenv("HOME"));
	else
		chdir(line + i);
	return ;
}
