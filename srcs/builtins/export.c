/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:13:02 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/26 14:24:13 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_shell	g_shell;

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
		if (compare_env(var, g_shell.envp[i]))
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

int	builtin_export(t_token command)
{
	int	i;
	t_var	var;
	char	**tab;
	
	if (command.arg_count)
	{
		i = 0;
		while (command.args[i])
		{
			if (command.args[i][0] == '=')
			{
				printf("minishell: %s is not a valid identifier\n", command.args[i]);
				return (1);
			}
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
	return (0);
}