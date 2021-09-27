/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/27 17:26:19 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*exp_stripe_quotes(char *str, size_t *length)
{
	size_t	i;
	char	*tmp;
	size_t	j;
	int		single_quote;

	i = 0;
	while (str[i])
	{
		if(str[i] == '"')
			*length -= 1;
		i++;
	}
	tmp = malloc(sizeof(char) * (*length + 1));
	tmp[*length] = '\0';
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '"')
		{
			tmp[j] = str[i];
			j++;
		}	
		i++;
	}
	return (tmp);
}

int
	exp_is_var(char c)
{
	if (
		(c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '9') ||
		(c == '_')
	)
		return (1);
	return (0);
}

char
	*exp_expanded(char *str, size_t *length)
{
	char	*tmp;
	size_t	i;
	size_t	beg;
	size_t	j;

	i = 0;
	// TODO: work on context

	while (str[i])
	{
		if (str[i] == '$')
		{
			beg = ++i;
			while (exp_is_var(str[i]))
				i++;
			tmp = malloc(sizeof(char) * (i - beg));
			j = 0;
			while (j < (i - beg))
			{
				tmp[j] = str[beg + j];
				j++;
			}
			tmp[j] = '\0';
			printf("CMD %s\n", tmp);
		}
		else
		{
			printf("char : %c\n",str[i]);
			i++;
		}
	}
	return (NULL);
}

char
	*exp_string(char *str)
{
	size_t	length;
	char	*tmp;

	length = ft_strlen(str);
	str = exp_stripe_quotes(str, &length);	
	tmp = exp_expanded(str, &length);

	printf("\nExpansion ------------------\n");
	printf("length: %zu\n", length);
	printf("string: %s\n", str);
	printf("expand: %s\n", tmp);
	printf("----------------------------\n");
	return (str);
}

void
	expand_command_token(t_token *command)
{
	size_t	size;
	char	*tmp;

	tmp = exp_string(command->str);

}