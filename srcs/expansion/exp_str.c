/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/29 21:47:56 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	exp_str_set_dest(char *tmp, char *dest, size_t *count)
{
	size_t	j;
	size_t	beg;

	if (tmp)
	{
		j = 0;
		beg = ft_strlen(tmp);
		while (j < beg)
		{
			dest[(*count)] = tmp[j];
			(*count)++;
			j++;
		}
		free(tmp);
	}
}

void
	exp_str_set_var(char *str, size_t *i, size_t *count, char *dest)
{
	char	*tmp;
	char	*itoa_tmp;
	size_t	c[2];

	c[0] = ++(*i);
	if (str[(*i)] == '?')
	{
		c[1] = 0;
		(*i)++;
		itoa_tmp = ft_itoa(g_shell.last_status);
		while (c[1] < ft_strlen(itoa_tmp))
		{
			dest[(*count)] = itoa_tmp[c[1]];
			(*count)++;
			c[1]++;
		}
		free(itoa_tmp);
	}
	else
	{
		while (exp_is_var(str[(*i)]))
			(*i)++;
		tmp = exp_current_var(str + c[0], (*i) - c[0]);
		exp_str_set_dest(tmp, dest, count);
	}
}

char
	*exp_str_set(char *str, size_t count, size_t *length)
{
	char	*dest;
	int		con;
	size_t	num[3];

	dest = malloc(sizeof(char) * (count + 1));
	num[1] = 0;
	count = 0;
	con = 0;
	while (str[num[1]])
	{
		con = exp_create_context(str[num[1]], con);
		if (str[num[1]] == '$' && con != 1)
			exp_str_set_var(str, &num[1], &count, dest);
		else
		{
			dest[count] = str[num[1]];
			count++;
			num[1]++;
		}
	}
	dest[count] = '\0';
	*length = count;
	return (dest);
}

char
	*exp_string(char *str)
{
	size_t	length;
	char	*tmp;
	char	*tmp2;

	length = ft_strlen(str);
	tmp2 = exp_str_set(str, exp_str_size(str), &length);
	tmp = exp_stripe_quotes(tmp2, &length);
	free (tmp2);
	return (tmp);
}
