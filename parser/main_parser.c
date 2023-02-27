#include "minishell.h"
int		ms_ismeta(char *c);
int		ms_count_words(char *line);
char	**ms_split(char *line);
int		get_word_len(char *line);

int	main(void)
{
	char	*line;
	char	**mat;

	line = readline("$> ");
	mat = ms_split(line);
	free(line);
	ft_free_mat(mat);
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

char	**ms_split(char *line)
{
	int		words;
	int		word_len;
	int		i;
	char	**mat;

	words = ms_count_words(line);
	if (words)
		mat = ft_calloc(sizeof(char *), (words + 1));
	printf("Words on | %s | > %d\n", line, words); //debug
	if (!mat)
		return (NULL);
	i = 0;
	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		word_len = get_word_len(line);
		mat[i] = ft_substr(line, 0, word_len); 
		line += word_len;
		while (ft_isspace(*line))
			line++;
		printf("mat[%d] > %s\n", i, mat[i]); //debug
		i++;
	}
	return (mat);
}

int	get_word_len(char *line)
{
	int	word_len;

	if (ms_ismeta(line))
		return (ms_ismeta(line));
	word_len = 0;
	while (*line && !ms_ismeta(line) && !ft_isspace(*line))
	{
		line++;
		word_len++;
	}
	return (word_len);
}
