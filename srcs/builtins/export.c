/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:13:02 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/27 13:04:23 by iharchi          ###   ########.fr       */
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
	var.name = ft_strdup(tab[0]);
	var.line = ft_strdup(line);
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
			return (&g_shell.envp[i]);
		i++;
	}
	return (NULL);
}

void	print_env()
{
	int		i;
	char	**tab;

	i = 0;
	while (g_shell.envp[i])
	{
		if (ft_strchr(g_shell.envp[i], '='))
		{
			tab = split_equals(g_shell.envp[i]);
			printf("export %s=\"%s\"\n", tab[0], tab[1]);
			free_tab(tab);
		}
		else
			printf("%s\n", g_shell.envp[i]);
		i++;
	}
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
			free(var.name);
		}
	}
	else
		print_env();
}