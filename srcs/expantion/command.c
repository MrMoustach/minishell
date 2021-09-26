/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/26 17:59:10 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	is_var_end(char c)
{
	if (
		(c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') ||
		(c >= '0' && c <= '9') ||
		c == '_'
	)
		return (1);
	return (0);
}

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
	printf("command name: %s\n", tmp);
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
			while (is_var_end(str[i]))
				i++;
			beg--;
			tmp = exp_command_name((str + beg + 1), i - beg - 1);
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
	*exp_replace_str(char *dest, char *src, size_t length)
{
	size_t	i;
	size_t	j;
	size_t	offset;
	size_t	count;
	size_t	beg;
	size_t	len;
	size_t	end;
	char	*tmp;

	i = 0;
	offset = i;
	while (src[i])
	{
		if (src[i] == '$')
		{
			beg = ++i;
			while (is_var_end(src[i]))
				i++;
			beg--;
			tmp = exp_command_name((src + beg + 1), i - beg - 1);
			if (tmp)
			{
				len = ft_strlen(tmp);
				j = 0;
				printf("ofsset: %zu\n", beg + j + offset);
				while (j < len)
				{
					dest[beg + j + offset] = tmp[j];
					j++;
				}
				offset += j - i + beg;
			}
			i--;
		}
		else
			dest[i] = src[i];
		i++;
	}

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
	tmp = malloc(sizeof(char) * (count + 1));
	ft_memset(tmp, 'x', count);
	tmp[count] = '\0';
	exp_replace_str(tmp, str, count);
	printf("%s\n", tmp);
	return (NULL);
}

void
	expand_command_token(t_token *command)
{
	printf("%s\n", command->str);
	exp_str(command->str);
	
}