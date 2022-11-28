/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguedes <gguedes@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:55:06 by gguedes           #+#    #+#             */
/*   Updated: 2022/11/28 17:57:15 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_remove_quotes(char *str)
{
	int		len;
	char	*new_str;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len <= 1)
		return (str);
	if (str[0] == '\"' && str[len - 1] == '\"')
		new_str = ft_substr(str, 1, len - 2);
	else if (str[0] == '\'' && str[len - 1] == '\'')
		new_str = ft_substr(str, 1, len - 2);
	else
		return (str);
	free(str);
	return (new_str);
}
