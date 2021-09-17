/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:39:15 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:31:18 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*temp1;
	unsigned char	p;

	i = 0;
	temp1 = (unsigned char *)s;
	p = (unsigned char)c;
	while (i < n)
	{
		if (temp1[i] == p)
			return (temp1 + i);
		i++;
	}
	return (NULL);
}
