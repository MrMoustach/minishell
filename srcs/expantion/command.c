/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/26 18:47:30 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*exp_strip_quotes(char *str)
{
	size_t	length;
	char	*tmp;
	int		i;

	length = ft_strlen(str);
	if (str[0] == '"' && str[length - 1] == '"')
	{
		tmp = malloc(sizeof(char) * length - 1);
		int	i=0;
		while(i < length - 2)
		{
			tmp[i] = str[i + 1];
			i++;
		}
		tmp[i] = '\0';
		free(str);
		str = tmp;
	}
	return (str);
}

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
	str = exp_strip_quotes(str);
	tmp = malloc(sizeof(char) * (count + 1));
	ft_memset(tmp, 'x', count); // TODO: remove later
	tmp[count] = '\0';
	exp_replace_str(tmp, str, count);
	printf("%s\n", tmp);
	return (NULL);
}

void
	expand_command_token(t_token *command)
{
	// printf("%s\n", command->str);
	exp_str(command->str);
	
}