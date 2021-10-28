/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_stripe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 08:04:44 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/28 16:21:09 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	exp_stripe_con(char *str, char *tmp, int *i, int *j)
{
	int	con;
	int	end_con;

	con = exp_create_context(str[(*i)], con);
	end_con = con;
	end_con = exp_create_context(str[(*i)], con);
	if ((str[(*i)] != '\'' && str[(*i)] != '\"') || (con && end_con))
	{
		tmp[(*j)] = str[(*i)];
		(*j)++;
	}
	(*i)++;
}

char
	*exp_stripe_quotes(char *str, size_t *length)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	tmp = malloc(sizeof(char) * (*length + 1));
	i = 0;
	j = 0;
	while (str[i])
		exp_stripe_con(str, tmp, &i, &j);
	tmp2 = malloc(sizeof(char) * (j));
	printf("-> %d\n", j);
	i = 0;
	while (i < j)
	{
		tmp2[i] = tmp[i];
		i++;
	}
	free(tmp);
	tmp2[j] = '\0';
	return (tmp2);
}
