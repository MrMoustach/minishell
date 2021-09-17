/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/17 21:04:30 by zed              ###   ########.fr       */
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

void	spliter (char *line)
{
	t_spliter	spliter;
	int	i;

	spliter.i = 0;
	spliter.in_quotes = 0;
	spliter.word_start = 0;
	while (line[spliter.i])
	{
		if (line[spliter.i] == ' ' || line[spliter.i + 1] == '\0')
		{
			i = spliter.i;
			if (line[spliter.i + 1] == '\0')
				i++;
			spliter.last_word = ft_substr(line, spliter.word_start, i - spliter.word_start);
			while (line[spliter.i] && line[spliter.i] == ' ')
				spliter.i++;
			spliter.word_start = spliter.i;
			printf("last word : %s\n", spliter.last_word);
			if (line[spliter.i + 1])
				continue ;
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