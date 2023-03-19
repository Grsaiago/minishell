#include "minishell.h"

/* daqui pra baixo tudo certin ok ?????? NÃO MEXE CARAIO*/
char	*ms_remove_quotes(char *line, int flag)
{
	char	*ret_word;
	int		i;
	int		len;

	if (!line)
		return (NULL);
	len = ft_strlen(line);
	ret_word = NULL;
	i = 0;
	if (!(ft_strchr(line, '\'') || ft_strchr(line, '\"')))
		return (line);
	ms_null_start_end_quotes(line);
	while (!line[i] && i < len)
		i++;
	while(i < len)
	{
		ret_word = ft_strjoin(ret_word, &line[i], 1);
		i += ft_strlen(&line[i]) + 1;
		while (!line[i] && i < len)
			i++;
	}
	if (flag)
		free(line);
	return (ret_word);
}

void	ms_null_start_end_quotes(char *line)
{
	int	next_quotes;

	if (!line)
		return ;
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
		{
			next_quotes = ms_find_next_quotes(line);
			*line = '\0';
			line += next_quotes;
			*line = '\0';
			line++;
		}
		else
			line++;
	}
	return ;
}
