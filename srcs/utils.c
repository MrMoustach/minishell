/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:04:52 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/05 09:59:02 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tab(char **tab)
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
	if (s[0] == '-' || s[0] == '+')
		i++;
	while (s[i])
		if (!ft_isdigit((int)s[i++]))
			return (0);
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
	while (str[i] == '0')
		i++;
	if (ft_strlen(&str[i]) > 19) // ?? You mean 19?
		return (255 * signe);
	while (str[i] >= '0' && (str[i] <= '9') && str[i] != '\0')
		n = (n * 10) + (str[i++] - '0');
	return (n * signe);
}

char	**add_to_array(char **array, char *str, int count)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count - 1)
	{
		tmp[i] = array[i];
		i++;
	}
	tmp[i++] = str;
	tmp[i] = NULL;
	if (count != 1)
		free (array);
	return (tmp);
}
