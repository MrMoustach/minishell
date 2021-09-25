/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:13:02 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/25 18:11:48 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_equals(char *str)
{
	int	i;
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

static char	*var_line(char *line)
{
	char	*ret;
	char	**tab;
	
	//TODO : free this split
	tab = split_equals(line);
	if (ft_strchr(line, '='))
	{
		ret = ft_strjoin(tab[0], "=\"");
		ret = ft_strjoin(ret, tab[1]);
		ret = ft_strjoin(ret, "\"");
	}
	else
		ret = ft_strdup(line);
	printf("%s\n", ret);
	return (ret);
}

void	builtin_export(t_token command)
{
	int	i;
	int	j;
	char	*ret;
	char	**tab;
	
	if (command.arg_count)
	{
		i = 0;
		while (command.args[i])
		{
			var_line(command.args[i]);
			i++;
		}
	}
	else
		builtin_env(command);
}