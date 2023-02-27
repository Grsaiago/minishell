#include "minishell.h"
int	ms_ismeta(char *c);
int	ms_count_words(char *line);

int	main(void)
{
	char	*line;

	line = readline("$> ");
	printf("Essa foi a linha: %s\nE as palavras são: |%d|\n", line, ms_count_words(line));
	free(line);
}

int	ms_count_words(char *line)
{
	unsigned int	words;

	while (*line && ft_isspace(*line))
		line++;
	words = 0;
	while (*line)
	{
		words++;
		while (ft_isspace(*line))
			line++;
		if (ms_ismeta(line))
			line += ms_ismeta(line);
		else if (*line && !ft_isspace(*line))
		{
			while (*line && !ft_isspace(*line) && !ms_ismeta(line))
				line++;
		}
		while (ft_isspace(*line))
			line++;
	}
	return (words);
}

int	ms_ismeta(char *c)
{
	if ((c[0] == '<' && c[1] == '<') || (c[0] == '>' && c[1] == '>'))
		return (2);
	else if (*c == '|' || *c == '>' || *c == '<')
		return (1);
	return (0);
}
