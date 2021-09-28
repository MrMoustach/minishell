/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 08:05:41 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/28 08:26:07 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	exp_is_var(char c)
{
	if (
		(c >= 'A' && c <= 'Z') ||
		(c >= 'a' && c <= 'z') ||
		(c >= '0' && c <= '9') ||
		(c == '_')
	)
		return (1);
	return (0);
}

char
	*exp_current_var(char *src, size_t end)
{
	char	*tmp;
	char	*val;
	size_t	i;

	i = 0;
	tmp = malloc(sizeof(char) * end);
	while (i < end)
	{
		tmp[i] = src[i];
		i++;
	}
	tmp[i] = '\0';
	return (ft_getenv(tmp));
}
