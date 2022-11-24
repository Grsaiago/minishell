/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_validate_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsaiago <gsaiago@student.42.rio>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:36:25 by gsaiago           #+#    #+#             */
/*   Updated: 2022/11/24 00:07:56 by gsaiago          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
char	***create_argv_array(t_shell s_shell)
{
	char	***argv_array;
	int		phrases;
	int		i;

	i = 0;
	if (s_shell->input_line)
		return (NULL);
	phrases = count_phrases(s_shell->input_line);
	argv_array = ft_calloc(sizeof(char *), phrases + 1);
	if (!argv_array)
		return (NULL);
	while (i < phrases)
	{
		argv_array[i] = 
		i++;
	}

}

char **create_argv(t_shell s_shell)
{
	char	**av;
	int		i;

	if (!s_shell->input_line)
		return (NULL);

}

char	**minishell_split(t_shell s_shell)
{
	int		quotes_len;
	int		i;
	char	**av;

	
}
*/

int	count_phrases(char *line)
{
	int i;
	int	phrases;

	i = 0;
	phrases = 1;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] == '"')
			i = ft_strchrn(line + i, '"');
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			if (line[i] == '>' || line[i] == '<')
				i++;
			phrases++;
		}
		i++;
	}
	return (phrases);
}

int	word_len(char *line)
{
	int	i;
	int	len;

	if (!line || !line[0])
		return (0);
	i = 0;
	len = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '"')
		len = ft_strchrn(line + i, '"');
	while (!ft_isspace(line[i + len]))
		len++;
	return (len);
}
/*
int	count_words(char *line)
{
	int	i;

	i = 0;


}
*/
