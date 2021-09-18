/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/18 22:41:26 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"

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

void	split_extra(t_spliter *spliter, char *line, char delim)
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
	{
		add_token(create_token(ft_chardup(delim, 1)), &(spliter->tokens));
	}
	spliter->i++;
	while (line[spliter->i] && line[spliter->i] == ' ')
		spliter->i++;
	spliter->word_start = spliter->i;
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
				}
			}
			else
			{
				spliter.in_quotes = 1;
				spliter.quotes = line[spliter.i];
			}
			spliter.i++;
			continue;
		}
		if (!spliter.in_quotes)
		{
			if (line[spliter.i] == '>' || line[spliter.i] == '<' || line[spliter.i] == '|' || line[spliter.i] == ';' || line[spliter.i] == '&')
			{
				split_extra(&spliter, line, line[spliter.i]);
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
				add_token(create_token(spliter.last_word), &(spliter.tokens));
				break ;
			}
		}
		spliter.i++;
	}
	return (spliter);
}

void	tokenizer(t_list *tokens)
{
	int	context;
	t_list	*tmp;
	char *str;
	
	context = 0;
	tmp = tokens;
	while (tmp) 
	{
		str = ((t_token *)tmp->content)->str;
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
			((t_token *)tmp->content)->type = REDIRECTION;
			((t_token *)tmp->content)->direction = RIGHT;
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
	envp = sort_env(envp);
	// (omar) TODO  : Provide the line, and work on history / readline stuff
	// (issam) TODO : parse line into idividual commands, expand what can be expanded, and escape stuff return data as a command struct

	if (ac > 1)
	{
		split = spliter(av[1]);
		tokenizer(split.tokens);
		tmp = split.tokens;
		while (tmp)
		{
			printf("TOKEN : %s\n", ((t_token *)tmp->content)->str);
			printf("TYPE : ");
			if (((t_token *)tmp->content)->type == COMMAND)
				printf("COMMAND\n");
			if (((t_token *)tmp->content)->type == ARG)
				printf("ARG\n");
			if (((t_token *)tmp->content)->type == FILES)
				printf("FILES\n");
			if (((t_token *)tmp->content)->type == REDIRECTION)
				printf("REDIRECTION\n");
			if (((t_token *)tmp->content)->type == APPEND)
				printf("APPEND\n");
			if (((t_token *)tmp->content)->type == END)
				printf("END\n");
			if (((t_token *)tmp->content)->type == AND)
				printf("AND\n");
			if (((t_token *)tmp->content)->type == RANDOM)
				printf("RANDOM\n");
			if (((t_token *)tmp->content)->type == PIPE)
				printf("PIPE\n");
			printf("--------------------------------\n");
			tmp = tmp->next;
		}
	}
}