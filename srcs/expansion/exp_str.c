/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/28 08:07:07 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	count = 0;
	// TODO: work on context

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
				count += ft_strlen(tmp_val);
		}
		else
		{
			count++;
			i++;
		}
	}
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
