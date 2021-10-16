/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 00:49:07 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/17 00:52:49 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	split_end(t_spliter *spliter, char *line)
{
	if (line[spliter->i + 1] == '\0')
	{
		spliter->last_word = ft_substr(line, spliter->word_start,
				spliter->i - spliter->word_start + 1);
		while (line[spliter->i] && line[spliter->i] == ' ')
			spliter->i++;
		spliter->word_start = spliter->i;
		if (*spliter->last_word != '\0')
			add_token(create_token(spliter->last_word),
				&(spliter->tokens));
		return (1);
	}
	return (0);
}

int	split_append(t_spliter *spliter, char *line)
{
	if (line[spliter->i] == '>' || line[spliter->i] == '<'
		|| line[spliter->i] == '|' || line[spliter->i] == ';'
		|| line[spliter->i] == '&')
	{
		spliter = split_extra(spliter, line, line[spliter->i]);
		return (1);
	}
	if (line[spliter->i] == ' ')
	{
		spliter->last_word = ft_substr(line, spliter->word_start,
				spliter->i - spliter->word_start);
		while (line[spliter->i] && line[spliter->i] == ' ')
			spliter->i++;
		spliter->word_start = spliter->i;
		add_token(create_token(spliter->last_word), &(spliter->tokens));
		if (line[spliter->i])
			return (1);
	}
	return (0);
}

void	split_quotes(t_spliter *spliter, char *line)
{
	if (line[spliter->i] == '\'' || line[spliter->i] == '\"')
	{
		if (spliter->in_quotes)
		{
			if (spliter->quotes == line[spliter->i])
			{	
				spliter->in_quotes = 0;
				spliter->quotes = '\0';
			}
		}
		else
		{
			spliter->in_quotes = 1;
			spliter->quotes = line[spliter->i];
		}
	}
}
