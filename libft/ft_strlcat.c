/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:42:23 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:37:46 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int		lendst;
	unsigned int		lensrc;
	int					i;

	i = -1;
	lensrc = ft_strlen(src);
	if (size == 0)
		return (lensrc);
	lendst = ft_strlen(dst);
	if (lendst >= size)
		lensrc = lensrc + size;
	else
		lensrc = lensrc + lendst;
	if (src == dst)
		return (lensrc);
	while (src[++i] && lendst < size - 1)
		dst[lendst++] = src[i];
	if (i > 0)
		dst[lendst] = '\0';
	return (lensrc);
}
