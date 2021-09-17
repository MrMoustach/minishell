/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 22:18:26 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:32:05 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	tmp;
	char			wtmp;

	tmp = n;
	if (n < 0)
	{
		tmp = -n;
		ft_putchar_fd('-', fd);
	}
	if (tmp / 10 > 0)
		ft_putnbr_fd(tmp / 10, fd);
	wtmp = '0' + tmp % 10;
	ft_putchar_fd(wtmp, fd);
}
