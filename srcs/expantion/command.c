/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/26 11:15:28 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*exp_command_name(char *str, size_t size)
{
	char	*tmp;
	size_t	i;

	tmp = malloc(sizeof(char) * size);
	i = 0;
	while (i < size)
	{
		tmp[i] = str[i];
		i++;
	}
	printf("%s\n", tmp);
	return (tmp);
}

size_t
	exp_new_size(char *str)
{
	size_t	i;
	size_t	count;
	size_t	beg;
	size_t	end;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			beg = i + 1;
			// TODO: add helper to know the end of variable
			while (str[i] != ' ' && str[i] != '\0' && str[i] != '.')
				i++;
			end = i;
			printf("%s\n", exp_command_name((str + beg), end - beg));
			// TODO: manage this with a helper
			if (str[i] != '\0')
				count++;
		}
		else
			count++;
		i++;
	}
	return (count);
}

void
	exp_str(char *str)
{
	size_t	count;

	count = exp_new_size(str);

	printf("%zu \n", count);
}

void
	expand_command_token(t_token *command)
{
	exp_str(command->str);
	
	printf("\n-----------\n");
	printf("command: %s \n", command->str);
	printf("-----------\n");
}