/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_stripe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 08:04:44 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/28 08:04:59 by omimouni         ###   ########.fr       */
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
