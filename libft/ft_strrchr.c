/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:52:52 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:39:36 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			tmp = (char *)s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (tmp);
}
