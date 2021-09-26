/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/26 14:28:23 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*exp_command_name(char *str, size_t size)
{
	char	*tmp;
	size_t	i;

	tmp = malloc(sizeof(char) * size + 1);
	i = 0;
	while (i < size)
	{
		tmp[i] = str[i];
		i++;
	}
	tmp[i] = '\0';
	return (ft_getenv(tmp));
}

size_t
	exp_new_size(char *str)
{
	size_t	i;
	size_t	count;
	size_t	beg;
	size_t	end;
	char	*tmp;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			beg = ++i;
			// TODO: add helper to know the end of variable
			while (str[i] != '\0')
				i++;
			tmp = exp_command_name((str + beg), i - beg);
			if (tmp)
				count += ft_strlen(tmp);
			i--;
		}
		else
			count++;
		i++;
	}
	return (count);
}

char
	*exp_replace_str(char *dest, char *src)
{
}


/**
 * Replace env var in a string
 */
char
	*exp_str(char *str)
{
	size_t	count;
	char	*tmp;

	count = exp_new_size(str);
	tmp = malloc(sizeof(char) * count);

	return (NULL);
}

void
	expand_command_token(t_token *command)
{

	exp_str(command->str);
}