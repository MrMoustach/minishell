/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/28 08:34:14 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t
	exp_str_size(char *str)
{
	size_t	count;
	size_t	i;
	size_t	beg;
	char	*tmp;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			beg = ++i;
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
	*exp_str_set(char *str, size_t count)
{
	char	*dest;
	char	*tmp;
	size_t	beg;
	size_t	i;
	size_t	j;

	dest = malloc(sizeof(count) * (count + 1));
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			beg = ++i;
			while (exp_is_var(str[i]))
				i++;
			tmp = exp_current_var(str + beg, i - beg);
			if (tmp)
			{
				j = 0;
				while (j < i - beg)
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
	return (dest);
}


// TODO: work on quotation stripe and context
char
	*exp_expanded(char *str, size_t *length)
{
	char	*tmp;
	char	*tmp_val;
	char	*tmp2;
	size_t	i;
	size_t	beg;
	size_t	j;
	size_t	count;

	i = 0;
	count = exp_str_size(str);

	tmp2 = malloc(sizeof(char) * (count + 1));
	ft_memset(tmp2, 'x', count);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			beg = ++i;
			while (exp_is_var(str[i]))
				i++;
			tmp = malloc(sizeof(char) * (i - beg));
			j = 0;
			while (j < (i - beg))
			{
				tmp[j] = str[beg + j];
				j++;
			}
			tmp[j] = '\0';
			tmp_val = ft_getenv(tmp);
			if (tmp_val)
			{
				j = 0;
				while (j < ft_strlen(tmp_val))
				{
					tmp2[count] = tmp_val[j];
					j++;
					count++;
				}
			}
		}
		else
		{
			tmp2[count] = str[i];
			count++;
			i++;
		}
	}
	tmp2[count] = '\0';
	printf("%s\n", tmp2);
	*length = count;
	return (tmp2);
}

char
	*exp_string(char *str)
{
	size_t	length;
	char	*tmp;

	length = ft_strlen(str);
	// TODO: fix this stripe
	str = exp_stripe_quotes(str, &length);
	// FIXME: Expand by context	
	tmp = exp_expanded(str, &length);

	printf("\nExpansion ------------------\n");
	printf("length: %zu\n", length);
	printf("string: %s\n", str);
	printf("expand: %s\n", tmp);
	printf("----------------------------\n");
	return (tmp);
}
