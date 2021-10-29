/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_str_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 11:12:26 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/29 17:23:25 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	exp_str_size_var(char *str, size_t *i, size_t *count)
{
	size_t	beg;
	char	*tmp;
	char	*itoa_tmp;

	beg = ++(*i);
	if (str[(*i)] == '?')
	{
		itoa_tmp = ft_itoa(g_shell.last_status);
		(*count) = ft_strlen(itoa_tmp);
		free(itoa_tmp);
	}
	else
	{
		while (exp_is_var(str[(*i)]))
			(*i)++;
		tmp = exp_current_var(str + beg, (*i) - beg);
		if (tmp)
		{
			(*count) += ft_strlen(tmp);
			free(tmp);
		}
	}
}

size_t
	exp_str_size(char *str)
{
	size_t	i;
	size_t	count;
	int		con;

	i = 0;
	count = 0;
	con = 0;
	while (str[i])
	{
		con = exp_create_context(str[i], con);
		if (str[i] == '$' && con != 1)
			exp_str_size_var(str, &i, &count);
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}
