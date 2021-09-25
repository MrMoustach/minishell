/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:33:29 by zed               #+#    #+#             */
/*   Updated: 2021/09/25 12:50:54 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab != NULL)
	{	
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
	
}

int	ft_is_number(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '-' || s[i] == '+' || ft_isdigit(s[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static int	ft_isws(char c)
{
	if (c == '\n' || c == '\f' || c == ' '
		|| c == '\r' || c == '\v' || c == '\t')
		return (1);
	return (0);
}

long long	ft_atol(const char *str)
{
	int				i;
	long long		n;
	int				signe;

	n = 0;
	i = 0;
	signe = 1;
	while (ft_isws(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			signe = -1;
	}
	while (str[i] >= '0' && (str[i] <= '9') && str[i] != '\0')
		n = (n * 10) + (str[i++] - '0');
	return (n * signe);
}