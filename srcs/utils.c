/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:04:52 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/24 19:04:54 by iharchi          ###   ########.fr       */
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

char	**add_to_top_array(char **array, char *str, int count)
{
	char	**tmp;
	int		i;
	
	tmp = malloc(sizeof(char *) * (count + 2));
	i = 0;
	tmp[0] = str;
	while (i < count)
	{
		tmp[i + 1] = array[i];
		i++;
	}
	tmp[i + 1] = NULL;

	// FIXME: this fuckedup the reparser
	// if (count != 1)
	// 	free (array);
	return (tmp);
}

char	*trim_starting_whitespaces(char *str)
{
	int		i;
	char	*tmp;
	
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'))
		i++;
	tmp = ft_strdup(&str[i]);
	free (str);
	return (tmp);
}
