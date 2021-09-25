/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:13:02 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/25 14:32:22 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*var_line(char *line)
{
	char	*ret;
	char	**tab;
	int		count;
	int		i;
	//TODO : free this split
	tab = ft_split(line, '=');
	count = table_count(tab);
	if (count <= 1)
	{
		ret = ft_strdup(line);
		ret = ft_strjoin(ret, ft_strdup("\"\""));
		return (ret);
	}
	ret = ft_strdup(tab[0]);
	ret = ft_strjoin(ret, ft_strdup("=\""));
	i = 1;
	while (tab[i])
		ret = ft_strjoin(ret, ft_strdup(tab[i++]));
	ret = ft_strjoin(ret, ft_strdup("\""));
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
			if (ft_strchr(command.args[i], '='))
			{
				printf("%s\n", var_line(command.args[i]));
			}
			else
				printf("%s\n", command.args[i]);
			i++;
		}
	}
	else
	{
		builtin_env(command);
	}
}