/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:33:47 by iharchi           #+#    #+#             */
/*   Updated: 2021/05/22 18:32:48 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp1;
	const char	*tmp2;

	tmp1 = dst;
	tmp2 = src;
	if (*tmp1 == '\0' && *tmp2 == '\0')
		return (NULL);
	if (ft_memcmp(tmp1, tmp2, len) == 0)
		return (dst);
	if (tmp2 < tmp1 && tmp1 < tmp2 + len)
	{
		tmp2 = tmp2 + len;
		tmp1 = tmp1 + len;
		while (len--)
			*--tmp1 = *--tmp2;
	}
	else
	{
		while (len--)
			*tmp1++ = *tmp2++;
	}
	return (dst);
}
