/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/18 16:31:31 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/minishell.h"
char	**sort_env(char **envp)
{
	int		i;
	char	*tmp;
	int		flag;

	while (1)
	{
		flag = 1;
		i = 0;
		while (envp[i + 1])
		{
			if (ft_strncmp(envp[i], envp[i + 1], ft_strlen(envp[i])) > 0)
			{
				tmp = envp[i + 1];
				envp[i + 1] = envp[i];
				envp[i] = tmp;
				flag = 0;	
			}
			i++;
		}
		if (flag)
			break ;
	}
	return (envp);
}

void	split_extra(t_spliter *spliter, char *line, char delim)
{
	if (spliter->i != spliter->word_start)
	{
		spliter->last_word = ft_substr(line, spliter->word_start, spliter->i - spliter->word_start);
		printf("last word : %s\n", spliter->last_word);
	}
	if (line[spliter->i + 1] == delim)
	{
		printf("last word : %c%c\n", delim, delim);
		spliter->i++;
	}
	else
		printf("last word : %c\n", delim);
	spliter->i++;
	while (line[spliter->i] && line[spliter->i] == ' ')
		spliter->i++;
	spliter->word_start = spliter->i;
}

void	spliter (char *line)
{
	t_spliter	spliter;

	spliter.i = 0;
	spliter.in_quotes = 0;
	spliter.word_start = 0;
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
				printf("last word : %s\n", spliter.last_word);
				if (line[spliter.i])
					continue ;
			}
			if (line[spliter.i + 1] == '\0')
			{
				spliter.last_word = ft_substr(line, spliter.word_start, spliter.i - spliter.word_start + 1);
				while (line[spliter.i] && line[spliter.i] == ' ')
					spliter.i++;
				spliter.word_start = spliter.i;
				printf("last word : %s\n", spliter.last_word);
				break ;
			}
		}
		spliter.i++;
	}
}

int	main(int ac, char **av, char **envp)
{
	envp = sort_env(envp);
	// (omar) TODO  : Provide the line, and work on history / readline stuff
	// (issam) TODO : parse line into idividual commands, expand what can be expanded, and escape stuff return data as a command struct

	if (ac > 1)
	{
		spliter(av[1]);
	}
}