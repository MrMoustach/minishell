/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/27 12:55:40 by omimouni         ###   ########.fr       */
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
	single_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && single_quote)
			single_quote = 0;
		if (str[i] == '\'')
			single_quote = 1;
		if(str[i] == '"' && single_quote)
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

char
	*exp_string(char *str)
{
	size_t	length;

	length = ft_strlen(str);
	str = exp_stripe_quotes(str, &length);
	

	printf("\nExpansion ------------------\n");
	printf("length: %zu\n", length);
	printf("string: %s\n", str);
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