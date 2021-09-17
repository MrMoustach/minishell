/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:00:52 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:38:57 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *needle, size_t n)
{
	unsigned int	i;
	int				j;

	i = 0;
	j = 0;
	if (*needle == '\0' || needle == NULL || (!str && !n))
		return ((char *)str);
	while (str[i] && i < n)
	{
		j = 0;
		while (needle[j] == str[j + i] && i + j < n)
		{
			if (needle[j + 1] == '\0')
				return ((char *)str + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
