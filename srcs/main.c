/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/20 09:32:22 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_chardup(char c, int n)
{
	char	*s;
	int		i;

	s = malloc(n + 1);
	i = 0;
	while (i < n)
		s[i++] = c;
	s[i] = '\0';
	return (s);
}

t_spliter	split_extra(t_spliter *spliter, char *line, char delim)
{
	if (spliter->i != spliter->word_start)
	{
		spliter->last_word = ft_substr(line, spliter->word_start, spliter->i - spliter->word_start);
		add_token(create_token(spliter->last_word), &(spliter->tokens));

	}
	if (line[spliter->i + 1] == delim)
	{
		add_token(create_token(ft_chardup(delim, 2)), &(spliter->tokens));
		spliter->i++;
	}
	else
		add_token(create_token(ft_chardup(delim, 1)), &(spliter->tokens));
	spliter->i++;
	while (line[spliter->i] && line[spliter->i] == ' ')
		spliter->i++;
	spliter->word_start = spliter->i;
	return (*spliter);
}

t_spliter spliter (char *line)
{
	t_spliter	spliter;

	spliter.i = 0;
	spliter.in_quotes = 0;
	spliter.word_start = 0;
	spliter.tokens = NULL;
	while (line[spliter.i])
	{
		if (line[spliter.i] == '\'' || line[spliter.i] == '\"')
		{
			if (spliter.in_quotes)
			{
				if (spliter.quotes == line[spliter.i])
				{	
					spliter.in_quotes = 0;
					spliter.quotes = '\0';
					// spliter.i++;
					// spliter.last_word = ft_substr(line, spliter.word_start, spliter.i - spliter.word_start);
					// while (line[spliter.i] && line[spliter.i] == ' ')
					// 	spliter.i++;
					// spliter.word_start = spliter.i;
					// add_token(create_token(spliter.last_word), &(spliter.tokens));
				}
			}
			else
			{
				spliter.in_quotes = 1;
				spliter.quotes = line[spliter.i];
			}
			// spliter.i++;
			// continue;
		}
		if (!spliter.in_quotes)
		{
			if (line[spliter.i] == '>' || line[spliter.i] == '<' || line[spliter.i] == '|' || line[spliter.i] == ';' || line[spliter.i] == '&')
			{
				spliter = split_extra(&spliter, line, line[spliter.i]);
				continue ;
			}
			if (line[spliter.i] == ' ')
			{
				spliter.last_word = ft_substr(line, spliter.word_start, spliter.i - spliter.word_start);
				while (line[spliter.i] && line[spliter.i] == ' ')
					spliter.i++;
				spliter.word_start = spliter.i;
				add_token(create_token(spliter.last_word), &(spliter.tokens));
				if (line[spliter.i])
					continue ;
			}
			if (line[spliter.i + 1] == '\0')
			{
				spliter.last_word = ft_substr(line, spliter.word_start, spliter.i - spliter.word_start + 1);
				while (line[spliter.i] && line[spliter.i] == ' ')
					spliter.i++;
				spliter.word_start = spliter.i;
				if (*spliter.last_word != '\0')
					add_token(create_token(spliter.last_word), &(spliter.tokens));
				break ;
			}
		}
		spliter.i++;
	}
	return (spliter);
}

// (issam) TODO : Clean up this shit
void	tokenizer(t_list *tokens)
{
	int	context;
	t_list	*tmp;
	char *str;
	t_token	*token;
	
	context = 0;
	tmp = tokens;
	while (tmp) 
	{
		str = ((t_token *)tmp->content)->str;
		token = ((t_token *)tmp->content);
		if (!ft_strncmp(str, "|", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = PIPE;
			context = 0;
		}
		else if (!ft_strncmp(str, ";", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = END;
			context = 0;
		}
		else if (!ft_strncmp(str, "&&", ft_strlen(str) ))
		{
			((t_token *)tmp->content)->type = RANDOM;
			context = 0;
		}
		else if (!ft_strncmp(str, "||", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = RANDOM;
			context = 0;
		}
		else if (!ft_strncmp(str, "&", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = AND;
			context = 0;
		}
		else if (!ft_strncmp(str, ">", ft_strlen(str)))
		{
			token->type = REDIRECTION;
			token->direction = RIGHT;
			context = 3;
		}
		else if (!ft_strncmp(str, ">>", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = APPEND;
			((t_token *)tmp->content)->direction = RIGHT;
			context = 3;
		}
		else if (!ft_strncmp(str, "<", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = REDIRECTION;
			((t_token *)tmp->content)->direction = LEFT;
			context = 3;
		}
		else if (!ft_strncmp(str, "<<", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = APPEND;
			((t_token *)tmp->content)->direction = LEFT;
			context = 3;
		}
		else
		{
			if (context == 0)
			{
				context = 1;
				((t_token *)tmp->content)->type = COMMAND;
			}
			else if (context == 1)
			{
				((t_token *)tmp->content)->type = ARG;
			}
			else
			{
				((t_token *)tmp->content)->type = FILES;
			}
		}
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_spliter split;
	t_list	*tmp;
	t_token	token;
	char	*line;
	envp = sort_env(envp);
	// (omar) TODO  : Provide the line, and work on history / readline stuff
	// (issam) TODO : parse line into idividual commands, expand what can be expanded, and escape stuff return data as a command struct
	using_history();
	while (1)
	{
		line = readline(FT_PROMPT);
		add_history(line);
		split = spliter(line);
		tokenizer(split.tokens);
		tmp = split.tokens;
		while (tmp)
		{
			token = *((t_token *)tmp->content);
			printf("TOKEN : %s\n", token.str);
			printf("TYPE : ");
			printf("%s\n", types[(int)token.type]);
			printf("--------------------------------\n");
			tmp = tmp->next;
		}
		free(line);
	}
}