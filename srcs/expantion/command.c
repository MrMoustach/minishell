/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/26 14:21:03 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*exp_command_name(char *str, size_t size)
{
	char	*tmp;
	size_t	i;


	printf("size: %zu\n", size);
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
			printf("x%sx\n", tmp);
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


/**
 * Replace env var in a string
 */
char
	*exp_str(char *str)
{
	size_t	count;

	count = exp_new_size(str);
	printf("%zu\n", count);
	return (NULL);
}

void
	expand_command_token(t_token *command)
{

	exp_str(command->str);
	
	printf("\n-----------\n");
	printf("command: %s \n", command->str);
	printf("-----------\n");
}