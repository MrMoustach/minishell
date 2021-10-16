/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:07:06 by zed               #+#    #+#             */
/*   Updated: 2021/10/17 00:50:56 by omimouni         ###   ########.fr       */
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

t_spliter	*split_extra(t_spliter *spliter, char *line, char delim)
{
	if (spliter->i != spliter->word_start)
	{
		spliter->last_word = ft_substr(line, spliter->word_start,
				spliter->i - spliter->word_start);
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
	return (spliter);
}

t_spliter	spliter(char *line)
{
	t_spliter	spliter;

	spliter.i = 0;
	spliter.in_quotes = 0;
	spliter.word_start = 0;
	spliter.tokens = NULL;
	while (line[spliter.i])
	{
		split_quotes(&spliter, line);
		if (!spliter.in_quotes)
		{
			if (split_append(&spliter, line))
				continue ;
			if (split_end(&spliter, line))
				break ;
		}
		spliter.i++;
	}
	if (spliter.in_quotes)
		g_shell.error = 1;
	return (spliter);
}
