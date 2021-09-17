/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:09:27 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:37:35 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*p;

	p = (char *)malloc(ft_strlen(str) + 1);
	if (!p)
		return (NULL);
	ft_strlcpy(p, str, ft_strlen(str) + 1);
	return (p);
}
