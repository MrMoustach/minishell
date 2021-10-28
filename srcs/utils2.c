/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:49:22 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/28 17:49:49 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
