/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 16:10:01 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/05 09:50:37 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*zero(void)
{
	char	*ret;

	ret = (char *)malloc(2);
	ret[0] = '0';
	ret[1] = '\0';
	return (ret);
}

static	long long	calculate(unsigned long long n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static	int	det_n(unsigned long long *tmp, long long n)
{
	if (n < 0)
	{
		*tmp = -n;
		return (1);
	}
	*tmp = (unsigned long long)n;
	return (0);
}

char	*ft_ltoa(long long n)
{
	long long			len;
	int					signe;
	unsigned long long	tmp;
	char				*ret;

	len = 0;
	signe = 0;
	tmp = n;
	if (n == 0)
		return (ret = zero());
	else
		signe = det_n(&tmp, n);
	len = calculate(tmp);
	ret = (char *)malloc(len + signe + 1);
	*(ret + len-- + signe) = '\0';
	while (tmp > 0)
	{
		*(ret + len + signe) = tmp % 10 + '0';
		len--;
		tmp /= 10;
	}
	if (signe)
		*ret = '-';
	return (ret);
}
