/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:13:02 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/26 17:23:03 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_shell	g_shell;

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

static t_var	var_line(char *line)
{
	char	*ret;
	char	**tab;
	t_var	var;
	
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
	var.name = ft_strdup(tab[0]);
	var.line = ret;
	free_tab(tab);
	return (var);
}

char	**get_address(char *var)
{
	int	i;

	i = 0;
	while (g_shell.envp[i])
	{
		if (!ft_strncmp(var, g_shell.envp[i], ft_strlen(var)))
		{
			return (&g_shell.envp[i]);
		}
		i++;
	}
	return (NULL);
}

void	builtin_export(t_token command)
{
	int	i;
	t_var	var;
	char	**tab;
	
	if (command.arg_count)
	{
		i = 0;
		while (command.args[i])
		{
			var = var_line(command.args[i]);
			if ((tab = get_address(var.name)))
			{
				free (*tab);
				*tab = var.line;
			}
			else
				ft_addenv(var.line);
			i++;
		}
	}
	else
		builtin_env(command);
}