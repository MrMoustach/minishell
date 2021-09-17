/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:27:43 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:31:00 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, void const *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*temp1;
	unsigned char	*temp2;
	unsigned char	p;

	i = 0;
	temp1 = (unsigned char *)d;
	temp2 = (unsigned char *)s;
	p = (unsigned char)c;
	if (!temp1 && !temp2 && !n && !c)
		return (d);
	while (i < n)
	{
		*(temp1 + i) = *(temp2 + i);
		if (*(temp2 + i) == p)
			return (d + i + 1);
		i++;
	}
	return (NULL);
}
