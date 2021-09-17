/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:12:23 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:25:04 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t e)
{
	void	*p;

	if (n == 0 || e == 0)
	{
		n = 1;
		e = 1;
	}
	p = malloc(n * e);
	if (p == NULL)
		return (NULL);
	ft_bzero(p, n * e);
	return (p);
}
