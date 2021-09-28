/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_stripe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 08:04:44 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/28 17:30:59 by omimouni         ###   ########.fr       */
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
	int		end_con;

	tmp = malloc(sizeof(char) * (*length + 1));
	ft_memset(tmp, 'x', *length);
	i = 0;
	j = 0;
	con = 0;
	while (str[i])
	{
		con = exp_create_context(str[i], con);
		end_con = con;
		end_con = exp_create_context(str[i], con);
		if (con && end_con)
		{
			printf("%c in quote %d %d\n", str[i], con, end_con);
			tmp[j] = str[i];
			j++;
		}
		i++;
	}
	tmp[*length] = '\0';
	printf("\nstripped sentence %s\n", tmp);
	return (tmp);
}
