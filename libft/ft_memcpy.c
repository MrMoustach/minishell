/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:14:22 by iharchi           #+#    #+#             */
/*   Updated: 2019/10/15 21:04:30 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	if (!dst && !src)
		return (NULL);
	temp1 = (unsigned char *)dst;
	temp2 = (unsigned char *)src;
	i = 0;
	if (!ft_memcmp(temp1, temp2, n) || (!temp1 && !temp2))
		return (dst);
	while (i < n)
	{
		temp1[i] = temp2[i];
		i++;
	}
	return (dst);
}
