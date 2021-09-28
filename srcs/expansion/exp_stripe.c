/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_stripe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 08:04:44 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/28 17:58:34 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*exp_stripe_quotes(char *str, size_t *length)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;
	int		con;
	int		end_con;

	tmp = malloc(sizeof(char) * (*length + 1));
	i = 0;
	j = 0;
	con = 0;

	// FIXME: Sig fault when unclosed quote
	while (str[i])
	{
		con = exp_create_context(str[i], con);
		end_con = con;
		end_con = exp_create_context(str[i], con);
		if ((str[i] != '\'' && str[i] != '\"') || con && end_con)
		{
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp2 = malloc(sizeof(char) * (j));
	i = 0;
	while (i < j)
	{
		tmp2[i] = tmp[i];
		i++;
	}
	tmp2[j] = '\0'; 
	return (tmp2);
}
