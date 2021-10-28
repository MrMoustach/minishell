/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/28 16:20:44 by omimouni         ###   ########.fr       */
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
	size_t	beg;
	size_t	j;

	beg = ++(*i);
	if (str[(*i)] == '?')
	{
		j = 0;
		(*i)++;
		itoa_tmp = ft_itoa(g_shell.last_status);
		while (j < ft_strlen(itoa_tmp))
		{
			dest[(*count)] = itoa_tmp[j];
			(*count)++;
			j++;
		}
		free(itoa_tmp);
	}
	else
	{
		while (exp_is_var(str[(*i)]))
			(*i)++;
		tmp = exp_current_var(str + beg, (*i) - beg);
		exp_str_set_dest(tmp, dest, count);
	}
}

char
	*exp_str_set(char *str, size_t count, size_t *length)
{
	char	*dest;
	char	*tmp;
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
