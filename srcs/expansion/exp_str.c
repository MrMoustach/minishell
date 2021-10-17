/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/17 09:26:57 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t
	exp_str_size(char *str)
{
	char	*tmp;
	size_t	i;
	size_t	count;
	size_t	beg;
	int		con;

	i = 0;
	count = 0;
	con = 0;
	while (str[i])
	{
		con = exp_create_context(str[i], con);
		if (str[i] == '$' && con != 1)
		{
			beg = ++i;
			
			if (str[i] == '?')
			{
				count = ft_strlen(ft_itoa(g_shell.last_status));
				break ;
			}
			
			while (exp_is_var(str[i]))
				i++;
			tmp = exp_current_var(str + beg, i - beg);
			if (tmp)
				count += ft_strlen(tmp);
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char
	*exp_str_set(char *str, size_t count, size_t *length)
{
	char	*dest;
	char	*tmp;
	size_t	beg;
	size_t	i;
	int		con;
	size_t	j;

	dest = malloc(sizeof(char) * (count + 1));
	i = 0;
	count = 0;
	con = 0;
	while (str[i])
	{
		con = exp_create_context(str[i], con);
		if (str[i] == '$' && con != 1)
		{	
			beg = ++i;
			if (str[i] == '?')
			{
				j = 0;
				while (j < ft_strlen(ft_itoa(g_shell.last_status)))
				{
					dest[count] = ft_itoa(g_shell.last_status)[j];
					count++;
					j++;
				}
				break ;
			}
			while (exp_is_var(str[i]))
				i++;
			tmp = exp_current_var(str + beg, i - beg);
			if (tmp)
			{
				j = 0;
				beg = ft_strlen(tmp);
				while (j < beg)
				{
					dest[count] = tmp[j];
					count++;	
					j++;
				}
			}
		}
		else
		{
			dest[count] = str[i];
			count++;
			i++;
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

	length = ft_strlen(str);
	tmp = exp_str_set(str, exp_str_size(str), &length);
	tmp = exp_stripe_quotes(tmp, &length);

	return (tmp);
}
