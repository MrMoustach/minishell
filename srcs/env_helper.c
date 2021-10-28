/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:52:05 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/28 17:52:20 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	table_count(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

char	**dup_env(char **envp)
{
	char	**table;
	int		count;

	count = table_count(envp);
	table = malloc(sizeof(char *) * (count + 1));
	table[count] = NULL;
	while (count--)
		table[count] = ft_strdup(envp[count]);
	return (table);
}

char	**split_equals(char *str)
{
	int		i;
	char	**tab;

	i = 0;
	while (str[i])
	{	
		if (str[i] == '=')
			break ;
		i++;
	}
	tab = malloc(sizeof(char *) * 3);
	tab[0] = ft_substr(str, 0, i);
	if (str[i + 1])
		tab[1] = ft_substr(str, i + 1, ft_strlen(str) - i);
	else
		tab[1] = ft_strdup("");
	tab[2] = NULL;
	return (tab);
}

int	compare_env(char *name, char *var)
{
	char	**tab;
	int		ret;

	tab = split_equals(var);
	ret = 0;
	if (!ft_strncmp(tab[0], name, ft_strlen(tab[0]) + 1))
		ret = 1;
	free_tab(tab);
	return (ret);
}
