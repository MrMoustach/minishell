/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_stripe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 08:04:44 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/29 17:55:07 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	exp_stripe_con(char *str, char *tmp, int p[])
{
	int	end_con;

	p[2] = exp_create_context(str[p[0]], p[2]);
	end_con = p[2];
	end_con = exp_create_context(str[p[0]], p[2]);
	if ((str[p[0]] != '\'' && str[p[0]] != '\"') || (p[2] && end_con))
	{
		tmp[p[1]] = str[p[0]];
		p[1]++;
	}
	p[0]++;
}

char
	*exp_stripe_quotes(char *str, size_t *length)
{
	char	*tmp;
	char	*tmp2;
	int		p[3];

	tmp = malloc(sizeof(char) * (*length + 1));
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	while (str[p[0]])
		exp_stripe_con(str, tmp, p);
	tmp2 = malloc(sizeof(char) * (p[1] + 1));
	p[0] = 0;
	while (p[0] < p[1])
	{
		tmp2[p[0]] = tmp[p[0]];
		p[0]++;
	}
	free(tmp);
	tmp2[p[1]] = '\0';
	return (tmp2);
}
