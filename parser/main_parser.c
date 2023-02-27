#include "minishell.h"
int		ms_ismeta(char *c);
int		ms_count_words(char *line);
int		get_word_len(char *line);
t_word	*ms_create_word_lst(char *line);
void	ms_lstadd_back(t_word **lst, t_word *new);
t_word	*ms_lstnew(void *word);
void	ms_lstclear(t_word **lst);
int		ms_word_assign_flag(char *word);
void	ms_word_lst_flag_init(t_word *word);
void	ms_lst_remove_if(t_word **head);

void	debug_func(t_word *word_lst)
{
	while (word_lst)
	{
		printf("Node word > %s\nNode flag > %d\n", word_lst->word, word_lst->flag); //debug
		printf("---------------\n");
		word_lst = word_lst->next;
	}
	return ;
}

int	main(void)
{
	char	*line;
	t_word	*word_lst;

	line = readline("$> ");
	word_lst = ms_create_word_lst(line);
	ms_word_lst_flag_init(word_lst);
	debug_func(word_lst);
	ms_lst_remove_if(&word_lst);
	printf("\nApós passar a lst_remove_if\n");
	debug_func(word_lst);
	ms_lstclear(&word_lst);
	free(line);
	return (0);
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
	else if (*c == '|') //*c == '>' || *c == '<')
		return (1);
	return (0);
}

t_word	*ms_create_word_lst(char *line)
{
	int		word_len;
	t_word	*new_word;
	t_word	*word_lst;


	word_lst = NULL;
	while (ft_isspace(*line))
		line++;
	while (*line)
	{
		word_len = get_word_len(line);
		new_word = ms_lstnew(ft_substr(line, 0, word_len));
		ms_lstadd_back(&word_lst, new_word);
		line += word_len;
		while (ft_isspace(*line))
			line++;
	}
	return (word_lst);
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

t_word	*ms_lstnew(void *word)
{
	t_word	*new;

	new = (t_word *)malloc(sizeof(t_word));
	if (!new)
		return (NULL);
	new->word = word;
	new->flag = 0;
	new->next = NULL;
	return (new);
}

void	ms_lstadd_back(t_word **lst, t_word *new)
{
	t_word	*last_node;

	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		last_node = *lst;
		while (last_node->next)
			last_node = last_node->next;
		last_node->next = new;
	}
	return ;
}

void	ms_lstclear(t_word **lst) 
{
	void	*aux;
	t_word	*node;

	if (!lst)
		return ;
	node = *lst;
	while (node)
	{
		aux = node->next;
		free(node->word);
		free(node);
		node = aux;
	}
	*lst = NULL;
	return ;
}

void	ms_word_lst_flag_init(t_word *word)
{
	while (word)
	{
		if (ms_word_assign_flag(word->word))
			word->flag = 1;
		word = word->next;
	}
	return ;
}

int	ms_word_assign_flag(char *word)
{
	while (*word)
	{
		if (*word == '>' || *word == '<')
			return(1);
		word++;
	}
	return (0);
}

void	ms_lst_remove_if(t_word **head)
{
	t_word	*node;

	if (!head || !*head)
		return ;
	node = *head;
	if (node->flag)
	{
		*head = node->next;
		free(node->word);
		free(node);
		ms_lst_remove_if(head);
	}
	node = *head;
	if (!head || !*head)
		return ;
	ms_lst_remove_if(&node->next);
	return ;
}
