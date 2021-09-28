/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_stripe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 08:04:44 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/28 16:50:38 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*exp_stripe_quotes(char *str, size_t *length)
{
	char	*tmp;
	int		i;
	int		j;
	int		con;

	tmp = malloc(sizeof(char) * (*length + 1));
	i = 0;
	j = 0;
	con = 0;
	while (str[i])
	{
		con = exp_create_context(str[i], con);
		if (str[i] != '\'' || str[i] != '"'){
			printf("%c in quotes %d \n", str[i], con);
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
